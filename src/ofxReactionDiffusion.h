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
    RD_MODE_GRAYSCOTT,
    RD_MODE_FITZHUGH_NAGUMO,
} ReactionDiffusionMode;

class ofxReactionDiffusion {

public:
    ofxReactionDiffusion();
    void allocate(int _width, int _height);
    void update();
    void draw(int _x=0, int _y=0, float _width=-1, float _height=-1);
    
    void setMode(ReactionDiffusionMode _mode) { mode = _mode;}

    void addSource(int _x, int _y, float _radius);
    void addObstacle(int _x, int _y, float _radius);
    void clearSources();
    void clearObstacles();
    void clearAll();

    void setPasses(float _passes) { passes = _passes; }
    void setFeed(float _feed) { feed = _feed; }
    void setKill(float _kill) { kill = _kill; }
    void setDu(float _Du) { Du = _Du; }
    void setDv(float _Dv) { Dv = _Dv; }

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
    
private:
    int width, height;
    ReactionDiffusionMode mode;
    
    ofFbo sourceFbo;
    ofFbo obstacleFbo;
    ofFbo bufferFbo;
    ofFbo coloredFbo;
    
    ofShader grayScottShader;
    ofShader fitzHughNagumoShader;
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
     FitzHugh-Nagumo Parameters
     */
    float a0;
    float a1;
    float epsilon;
    float delta;
    float k1;
    float k2;
    float k3;
    
    /*
     Gray-Scott Parameters
     */
    float feed;
    float kill;
    float Du;
    float Dv;
};
