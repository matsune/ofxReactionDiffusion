//
//  ofReactionDiffusion.h
//
//  Created by Yuma Matsune on 2016/10/25.
//
//
#pragma once

#include "ofMain.h"

#define STRINGIFY(A) #A

typedef enum {
    RD_MODE_GRAY_SCOTT,
    RD_MODE_FITZHUGH_NAGUMO,
    RD_MODE_BELOUSOV_ZHABOTINSKY,
    RD_MODE_WORM
} ReactionDiffusionMode;

class ofxReactionDiffusion {

public:
    ofxReactionDiffusion();
    void allocate(int _width, int _height, float _scale=1.0);
    void update();
    void draw(int _x=0, int _y=0, float _width=-1, float _height=-1);
    
    void setMode(ReactionDiffusionMode _mode) { mode = _mode;}

    void addSource(int _x, int _y, float _radius);
    void addObstacle(int _x, int _y, float _radius);
    void clearSources();
    void clearObstacles();
    void clearAll();

    void setColor1(float _r, float _g, float _b) { color1.r = _r; color1.g = _g; color1.b = _b; }
    void setColor2(float _r, float _g, float _b) { color2.r = _r; color2.g = _g; color2.b = _b; }
    void setColor3(float _r, float _g, float _b) { color3.r = _r; color3.g = _g; color3.b = _b; }
    void setColor4(float _r, float _g, float _b) { color4.r = _r; color4.g = _g; color4.b = _b; }
    void setColor5(float _r, float _g, float _b) { color5.r = _r; color5.g = _g; color5.b = _b; }
    
    void setColor1Threshold(float _thresh) { color1.a = _thresh; }
    void setColor2Threshold(float _thresh) { color2.a = _thresh; }
    void setColor3Threshold(float _thresh) { color3.a = _thresh; }
    void setColor4Threshold(float _thresh) { color4.a = _thresh; }
    void setColor5Threshold(float _thresh) { color5.a = _thresh; }
    
    ofFloatColor getColor1() { return color1; }
    ofFloatColor getColor2() { return color2; }
    ofFloatColor getColor3() { return color3; }
    ofFloatColor getColor4() { return color4; }
    ofFloatColor getColor5() { return color5; }
    
    /*
     Common Paramters
     */
    void setPasses(float _passes) { passes = _passes; }
    
    float getPasses() { return passes; }
    
    /*
     Gray-Scott
     */
    void setFeed(float _feed) { feed = _feed; }
    void setKill(float _kill) { kill = _kill; }
    void setDu(float _Du) { Du = _Du; }
    void setDv(float _Dv) { Dv = _Dv; }
    
    float getFeed() { return feed; }
    float getKill() { return kill; }
    float getDu() { return Du; }
    float getDv() { return Dv; }
    
    /*
     FitzHugh-Nagumo
     */
    void setA0(float _a0) { a0 = _a0; }
    void setA1(float _a1) { a1 = _a1; }
    void setEpsilon(float _epsilon) { epsilon = _epsilon; }
    void setDelta(float _delta) { delta = _delta; }
    void setK1(float _k1) { k1 = _k1; }
    void setK2(float _k2) { k2 = _k2; }
    void setK3(float _k3) { k3 = _k3; }
    
    float getA0() { return a0; }
    float getA1() { return a1; }
    float getEpsilon() { return epsilon; }
    float getDelta() { return delta; }
    float getK1() { return k1; }
    float getK2() { return k2; }
    float getK3() { return k3; }
    
    /*
     Belousov-Zhabotinsky
     */
    void setAlpha(float _alpha) { alpha = _alpha; }
    void setBeta(float _beta) { alpha = _beta; }
    void setGamma(float _gamma) { gamma = _gamma; }
    
    float getAlpha() { return alpha; }
    float getBeta() { return beta; }
    float getGamma() { return gamma; }
    
    /*
     Worm
     */
    void setConstA(float _constA) { constA = _constA; }
    void setConstB(float _constB) { constB = _constB; }
    
    void getConstA() { return constA; }
    void getConstB() { return constB; }

private:
    int width, height;
    float scale;
    ReactionDiffusionMode mode;
    
    ofFbo sourceFbo;
    ofFbo obstacleFbo;
    ofFbo bufferFbo;
    ofFbo coloredFbo;
    
    /// Gray-Scott
    ofShader gsShader;
    /// FitzHugh-Nagumo
    ofShader fhnShader;
    /// Belousov-Zhabotinsky
    ofShader bzShader;
    /// Worm
    ofShader wormShader;
    
    ofShader coloringShader;
    
    ofFloatColor color1;
    ofFloatColor color2;
    ofFloatColor color3;
    ofFloatColor color4;
    ofFloatColor color5;
    
    /*
     Common Paramters
     */
    float passes;
    
    /*
     Gray-Scott
     */
    float feed;
    float kill;
    float Du;
    float Dv;
    
    /*
     FitzHugh-Nagumo
     */
    float a0;
    float a1;
    float epsilon;
    float delta;
    float k1;
    float k2;
    float k3;
    
    /*
     Belousov-Zhabotinsky
     */
    float alpha;
    float beta;
    float gamma;
    
    /*
     Worm
     */
    float constA;
    float constB;
};
