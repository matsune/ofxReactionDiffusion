//
//  ofxReactionDiffusion.cpp
//
//  Created by Yuma Matsune on 2016/10/25.
//
//

#include "ofxReactionDiffusion.h"

ofxReactionDiffusion::ofxReactionDiffusion() {
    mode = RD_MODE_GRAY_SCOTT;
    
    passes = 0.2;
    
    feed = 0.0195;
    kill = 0.04;
    Du   = 0.25;
    Dv   = 0.195;
    
    a0      = 0.459184;
    a1      = 0.780612;
    epsilon = 0.642857;
    delta   = 3.0;
    k1      = 1.63776;
    k2      = 0.336735;
    k3      = 2.29592;
    
    alpha = 1.0;
    beta  = 1.0;
    gamma = 1.0;
    
    color1.set(   0.0,    0.0,    0.0, 0.0);
    color2.set(   0.0,  0.403, 0.6836, 0.2);
    color3.set(0.7857, 0.0816, 0.7347, 0.4);
    color4.set(   1.0, 0.1632, 0.4948, 0.6);
    color5.set(  0.02,   0.78,  0.918, 0.8);
    
    string grayScott = STRINGIFY(
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
    gsShader.unload();
    gsShader.setupShaderFromSource(GL_FRAGMENT_SHADER, grayScott);
    gsShader.linkProgram();
    
    string fitzHughNagumo = STRINGIFY(
                                      float kernel[9];
                                      vec2 offset[9];
                                      
                                      uniform float passes;
                                      uniform float a0;
                                      uniform float a1;
                                      uniform float epsilon;
                                      uniform float delta;
                                      uniform float k1;
                                      uniform float k2;
                                      uniform float k3;
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

                                          float du = (k1 * u) - (k2 * pow(u, 2.0)) - pow(u, 3.0) - v + lap.x;
                                          float dv = epsilon * (k3 * u - a1 * v - a0) + delta * lap.y;
                                          u += du * passes * 0.1;
                                          v += dv * passes * 0.1;
                                          gl_FragColor = vec4(clamp(u, 0.0, 1.0), 0, clamp(v, 0.0, 1.0), 1.0);
                                      }
                                    );
    fhnShader.unload();
    fhnShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fitzHughNagumo);
    fhnShader.linkProgram();
    
    string belousovZhabotinsky = STRINGIFY(
                                      vec2 offset[9];
                                      
                                      uniform float passes;
                                      uniform float alpha;
                                      uniform float beta;
                                      uniform float gamma;
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

                                          vec3 source = vec3(0);
                                          for(int i=0; i<9; i++){
                                              source += texture2DRect(tex0, st + offset[i]).rgb;
                                          }
                                          source /= 9.0;

                                          float a = source.r + source.r * ((alpha * (source.g * gamma)) - source.b) * passes;
                                          float b = source.g + source.g * ((beta * source.b) - (alpha * source.r)) * passes;
                                          float c = source.b + source.b * ((gamma * source.r) - (beta * source.g)) * passes;
                                          
                                          source.r = a;
                                          source.g = b;
                                          source.b = c;
                                          
                                          gl_FragColor = vec4(source, 1.0);
                                      }
                                      );
    bzShader.unload();
    bzShader.setupShaderFromSource(GL_FRAGMENT_SHADER, belousovZhabotinsky);
    bzShader.linkProgram();
    
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

void ofxReactionDiffusion::allocate(int _width, int _height, float _scale) {
    width = _width;
    height = _height;
    scale = _scale;
    
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
    switch (mode) {
        case RD_MODE_GRAY_SCOTT:
            gsShader.begin();
            gsShader.setUniform1f("passes", passes);
            gsShader.setUniform1f("feed", feed);
            gsShader.setUniform1f("kill", kill);
            gsShader.setUniform1f("Du", Du);
            gsShader.setUniform1f("Dv", Dv);
            bufferFbo.draw(0, 0);
            gsShader.end();
            break;
        case RD_MODE_FITZHUGH_NAGUMO:
            fhnShader.begin();
            fhnShader.setUniform1f("passes", passes);
            fhnShader.setUniform1f("a0", a0);
            fhnShader.setUniform1f("a1", a1);
            fhnShader.setUniform1f("epsilon", epsilon);
            fhnShader.setUniform1f("delta", delta);
            fhnShader.setUniform1f("k1", k1);
            fhnShader.setUniform1f("k2", k2);
            fhnShader.setUniform1f("k3", k3);
            bufferFbo.draw(0, 0);
            fhnShader.end();
            break;
        case RD_MODE_BELOUSOV_ZHABOTINSKY:
            bzShader.begin();
            bzShader.setUniform1f("passes", passes);
            bzShader.setUniform1f("alpha", alpha);
            bzShader.setUniform1f("beta", beta);
            bzShader.setUniform1f("gamma", gamma);
            bufferFbo.draw(0, 0);
            bzShader.end();
            break;
        default:
            break;
    }
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

void ofxReactionDiffusion::draw(int _x, int _y, float _width, float _height) {
    if (_width < 0) _width = width;
    if (_height < 0) _height = height;
    
    coloredFbo.draw(_x, _y, _width/scale, _height/scale);
}

void ofxReactionDiffusion::addSource(int _x, int _y, float _radius) {
    sourceFbo.begin();
    ofSetColor(100, 100, 120);
    ofDrawCircle(_x * scale, _y * scale, _radius * scale);
    sourceFbo.end();
}

void ofxReactionDiffusion::addObstacle(int _x, int _y, float _radius) {
    obstacleFbo.begin();
    ofSetColor(255, 0, 0);
    ofDrawCircle(_x * scale, _y * scale, _radius * scale);
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
