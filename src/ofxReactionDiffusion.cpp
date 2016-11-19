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
    
    grayScottShader.load("shader/grayscott");
    coloringShader.load("shader/color");
    
    color1.set(0.0, 0.0, 0.0, 0.0);
    color2.set(0.0, 0.5, 0.0, 0.2);
    color3.set(0.0, 1.0, 0.0, 0.4);
    color4.set(0.0, 0.5, 0.0, 0.6);
    color5.set(0.0, 1.0, 0.0, 0.8);
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
