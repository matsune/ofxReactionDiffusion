#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
//	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	
	ofGLFWWindowSettings setting;
    setting.width = 800;
    setting.height = 800;
    setting.setGLVersion(3, 2);
    ofCreateWindow(setting);
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
