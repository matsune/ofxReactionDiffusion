#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);

    rd.allocate(ofGetWidth(), ofGetHeight());
    
    gui.setup();
    gui.setName("Parameters");
    gui.add(mode.setup("Mode", 0, 0, 2));
    gui.add(passes.setup("Passes", rd.getPasses(), 0.01, 1.5));

    gui.add(gs.setup());
    gs.setName("Gray Scott");
    gs.add(feed.setup("Feed", rd.getFeed(), 0, 1.0));
    gs.add(kill.setup("Kill", rd.getKill(), 0, 1.0));
    gs.add(Du.setup("Du", rd.getDu(), 0, 1.0));
    gs.add(Dv.setup("Dv", rd.getDv(), 0, 1.0));
    
    gui.add(fhn.setup());
    fhn.setName("Fitz-Hugh Nagumo");
    fhn.add(a0.setup("a0", rd.getA0(), 0, 1.0));
    fhn.add(a1.setup("a1", rd.getA1(), 0, 1.0));
    fhn.add(epsilon.setup("Epsilon", rd.getEpsilon(), 0, 1.5));
    fhn.add(delta.setup("Delta", rd.getDelta(), 0, 1.0));
    fhn.add(k1.setup("K1", rd.getK1(), 0.001, 3.0));
    fhn.add(k2.setup("K2", rd.getK2(), 0.001, 3.0));
    fhn.add(k3.setup("K3", rd.getK3(), 0.001, 3.0));
    
    gui.add(bz.setup());
    bz.setName("Belousov Zhabotinsky");
    bz.add(alpha.setup("Alpha", rd.getAlpha(), 0, 1.0));
    bz.add(beta.setup("Beta", rd.getBeta(), 0, 1.0));
    bz.add(gamma.setup("Gamma", rd.getGamma(), 0, 1.0));
    
    colors.setup();
    colors.setPosition(ofGetWidth() - colors.getWidth(), 0);
    colors.setName("Colors");
    colors.add(color1.setup("Color 1", 0.0 , 0, 1.0));
    colors.add(thresh1.setup("Thresh 1", 0.0 , 0, 1.0));
    colors.add(color2.setup("Color 2", 0.25, 0, 1.0));
    colors.add(thresh2.setup("Thresh 2", 0.2 , 0, 1.0));
    colors.add(color3.setup("Color 3", 0.5 , 0, 1.0));
    colors.add(thresh3.setup("Thresh 3", 0.4 , 0, 1.0));
    colors.add(color4.setup("Color 4", 0.75, 0, 1.0));
    colors.add(thresh4.setup("Thresh 4", 0.6 , 0, 1.0));
    colors.add(color5.setup("Color 5", 1.0 , 0, 1.0));
    colors.add(thresh5.setup("Thresh 5", 0.8 , 0, 1.0));
}

//--------------------------------------------------------------
void ofApp::update(){
    rd.setPasses(passes);

    switch (mode) {
        case 0:
            rd.setMode(RD_MODE_GRAY_SCOTT);
            rd.setGrayScottParams(feed, kill, Du, Dv);
            break;
        case 1:
            rd.setMode(RD_MODE_FITZHUGH_NAGUMO);
            rd.setFhnParams(a0, a1, epsilon, delta, k1, k2, k3);
            break;
        case 2:
            rd.setMode(RD_MODE_BELOUSOV_ZHABOTINSKY);
            rd.setBzParams(alpha, beta, gamma);
            break;
        default:
            break;
    }

    rd.setColor1(color1);
    rd.setColor1Threshold(thresh1);
    rd.setColor2(color2);
    rd.setColor2Threshold(thresh2);
    rd.setColor3(color3);
    rd.setColor3Threshold(thresh3);
    rd.setColor4(color4);
    rd.setColor4Threshold(thresh4);
    rd.setColor5(color5);
    rd.setColor5Threshold(thresh5);
    
    rd.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    rd.draw();
    gui.draw();
    colors.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

    if (button == 0) {
        rd.addSource(x, y, 5);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
