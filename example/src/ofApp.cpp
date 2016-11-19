#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    rd.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
    rd.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    rd.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'c')
        rd.clearAll();
    if (key == 's')
        rd.clearSources();
    if (key == 'o')
        rd.clearObstacles();
    if (key == 'g')
        rd.setMode(RD_MODE_GRAYSCOTT);
    if (key == 'f')
        rd.setMode(RD_MODE_FITZHUGH_NAGUMO);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if (button == 0)
        rd.addSource(x, y, 5);
    if (button == 2)
        rd.addObstacle(x, y, 5);
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
