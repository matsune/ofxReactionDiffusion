#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxReactionDiffusion.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    void clear();
    
    ofxReactionDiffusion rd;
    
    
    ofxPanel gui;
    ofxIntSlider mode;
    ofxFloatSlider passes;
    ofxButton clearButton;
    
    ofxGuiGroup gs;
    ofxFloatSlider feed, kill, Du, Dv;
    
    ofxGuiGroup fhn;
    ofxFloatSlider a0, a1, epsilon, delta, k1, k2, k3;
    
    ofxGuiGroup bz;
    ofxFloatSlider alpha, beta, gamma;
    
    ofxGuiGroup worm;
    ofxFloatSlider constA, constB;
    
    ofxPanel colors;
    ofxFloatColorSlider color1, color2, color3, color4, color5;
    ofxFloatSlider thresh1, thresh2, thresh3, thresh4, thresh5;
};
