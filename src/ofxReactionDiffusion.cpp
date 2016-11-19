//
//  ofxReactionDiffusion.cpp
//
//  Created by Yuma Matsune on 2016/10/25.
//
//

#include "ofxReactionDiffusion.h"

ofxReactionDiffusion::ofxReactionDiffusion() {
    passes = 0.6;
    feed = 0.0195;
    kill = 0.04;
    Du = 0.25;
    Dv = 0.195;
    
    color1.set(0.0, 0.0, 0.0, 0.0);
    color2.set(0.0, 0.5, 0.0, 0.2);
    color3.set(0.0, 1.0, 0.0, 0.4);
    color4.set(0.0, 0.5, 0.0, 0.6);
    color5.set(0.0, 1.0, 0.0, 0.8);
    
    string grayscottFragment = STRINGIFY(
                                    float kernel[9];
                                    vec2 offset[9];
                                    
                                    uniform float passes;
                                    uniform float feed;
                                    uniform float kill;
                                    uniform float Du;
                                    uniform float Dv;
                                    uniform sampler2DRect tex0;
                                    
                                    void main(){
                                        vec2 st = gl_TexCoord[0].st;
                                        
                                        offset[0] = vec2( 0.0, -1.0);
                                        offset[1] = vec2(-1.0,  0.0);
                                        offset[2] = vec2( 0.0,  0.0);
                                        offset[3] = vec2( 1.0,  0.0);
                                        offset[4] = vec2( 0.0,  1.0);
                                        
                                        offset[5] = vec2(-1.0, -1.0);
                                        offset[6] = vec2( 1.0, -1.0);
                                        offset[7] = vec2(-1.0,  1.0);
                                        offset[8] = vec2( 1.0,  1.0);
                                        
                                        kernel[0] = 1.0;
                                        kernel[1] = 1.0;
                                        kernel[2] = -6.82842712;
                                        kernel[3] = 1.0;
                                        kernel[4] = 1.0;
                                        
                                        kernel[5] = 0.707106781;
                                        kernel[6] = 0.707106781;
                                        kernel[7] = 0.707106781;
                                        kernel[8] = 0.707106781;
                                        
                                        vec2 lap = vec2(0.0, 0.0);
                                        for(int i=0; i<9; i++){
                                            vec2 tmp = texture2DRect(tex0, st + offset[i]).rb;
                                            lap += tmp * kernel[i];
                                        }
                                        
                                        float u = texture2DRect(tex0, st).r;
                                        float v = texture2DRect(tex0, st).b;
                                        float uvv = u*v*v;
                                        float du = Du * lap.x - uvv + feed * (1.0 - u);
                                        float dv = Dv * lap.y + uvv - (feed + kill)*v;
                                        u += du * passes;
                                        v += dv * passes;
                                        gl_FragColor = vec4(clamp(u, 0.0, 1.0), 0, clamp(v, 0.0, 1.0), 1.0);
                                    }
                                );
    grayScottShader.unload();
    grayScottShader.setupShaderFromSource(GL_FRAGMENT_SHADER, grayscottFragment);
    grayScottShader.linkProgram();
    
    string coloringFragment = STRINGIFY(
                                   uniform vec4 color1;
                                   uniform vec4 color2;
                                   uniform vec4 color3;
                                   uniform vec4 color4;
                                   uniform vec4 color5;
                                   uniform sampler2DRect tex0;
                                   
                                   void main(){
                                       vec2 st = gl_TexCoord[0].st;
                                       
                                       float value = texture2DRect(tex0, st).b;
                                       float a;
                                       vec3 col;
                                       
                                       if(value <= color1.a)
                                           col = color1.rgb;
                                       if(value > color1.a && value <= color2.a)
                                       {
                                           a = (value-color1.a)/(color2.a-color1.a);
                                           col = mix(color1.rgb, color2.rgb, a);
                                       }
                                       if(value > color2.a && value <= color3.a)
                                       {
                                           a = (value-color2.a)/(color3.a-color2.a);
                                           col = mix(color2.rgb, color3.rgb, a);
                                       }
                                       if(value > color3.a && value <= color4.a)
                                       {
                                           a = (value-color3.a)/(color4.a-color3.a);
                                           col = mix(color3.rgb, color4.rgb, a);
                                       }
                                       if(value > color4.a && value <= color5.a)
                                       {
                                           a = (value - color4.a)/(color5.a - color4.a);
                                           col = mix(color4.rgb, color5.rgb, a);
                                       }
                                       if(value > color5.a)
                                           col = color5.rgb;
                                       
                                       gl_FragColor = vec4(col,1.0);
                                   }
                               );
    coloringShader.unload();
    coloringShader.setupShaderFromSource(GL_FRAGMENT_SHADER, coloringFragment);
    coloringShader.linkProgram();
}

void ofxReactionDiffusion::allocate(int _width, int _height) {
    width = _width;
    height = _height;
    
    sourceFbo.allocate(_width, _height);
    bufferFbo.allocate(_width, _height);
    obstacleFbo.allocate(_width, _height);
    coloredFbo.allocate(_width, _height);

    clearAll();
}


void ofxReactionDiffusion::update() {
    bufferFbo.begin();
        sourceFbo.draw(0, 0);
        obstacleFbo.draw(0, 0);
    bufferFbo.end();
    
    sourceFbo.begin();
        grayScottShader.begin();
            grayScottShader.setUniform1f("passes", passes);
            grayScottShader.setUniform1f("feed", feed);
            grayScottShader.setUniform1f("kill", kill);
            grayScottShader.setUniform1f("Du", Du);
            grayScottShader.setUniform1f("Dv", Dv);
            bufferFbo.draw(0, 0);
        grayScottShader.end();
    sourceFbo.end();
    
    coloredFbo.begin();
        coloringShader.begin();
            coloringShader.setUniform4f("color1", color1.r, color1.g, color1.b, color1.a);
            coloringShader.setUniform4f("color2", color2.r, color2.g, color2.b, color2.a);
            coloringShader.setUniform4f("color3", color3.r, color3.g, color3.b, color3.a);
            coloringShader.setUniform4f("color4", color4.r, color4.g, color4.b, color4.a);
            coloringShader.setUniform4f("color5", color5.r, color5.g, color5.b, color5.a);
            sourceFbo.draw(0, 0);
        coloringShader.end();
    coloredFbo.end();
}

void ofxReactionDiffusion::draw() {
    coloredFbo.draw(0, 0);
}

void ofxReactionDiffusion::addSource(int _x, int _y, float _radius) {
    sourceFbo.begin();
    ofSetColor(0, 0, 220);
    ofDrawCircle(_x, _y, _radius);
    sourceFbo.end();
}

void ofxReactionDiffusion::addObstacle(int _x, int _y, float _radius) {
    obstacleFbo.begin();
    ofSetColor(255, 0, 0);
    ofDrawCircle(_x, _y, _radius);
    obstacleFbo.end();
}

void ofxReactionDiffusion::clearSources() {
    sourceFbo.begin();
    ofBackground(255, 0, 0);
    sourceFbo.end();
}

void ofxReactionDiffusion::clearObstacles() {
    obstacleFbo.begin();
    ofClear(255, 0, 0);
    obstacleFbo.end();
}

void ofxReactionDiffusion::clearAll() {
    clearSources();
    clearObstacles();
}
