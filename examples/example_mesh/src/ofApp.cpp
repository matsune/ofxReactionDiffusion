#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);
    ofEnableDepthTest();

    /*
     ofEasyCam
     */
    cam.setupPerspective(true, 60, 10, 0, ofVec2f(0.0, 0.0));
    cam.setDistance(250);

    /*
     ofxReactionDiffusion
     */
    scale = 3.0;
    
    rd.allocate(ofGetWidth(), ofGetHeight(), scale);
    rd.setPasses(0.998265);
    rd.setGrayScottParams(0.0239133, 0.0501276, 0.178571, 0.212041);
    
    /// add Initial Sources
    rd.getSourceFbo().begin();
    ofSetColor(0, 0, 200);
    ofDrawRectangle(100, 100, 100, 100);
    rd.getSourceFbo().end();
    
    /*
     Mesh
     */
    mesh.setMode(OF_PRIMITIVE_POINTS);

    for (int y = 0; y < ofGetHeight()/scale; y++) {
        for (int x = 0; x < ofGetWidth()/scale; x++) {
            mesh.addVertex(ofVec3f(0, 0, 0));
            mesh.addTexCoord(ofVec2f(y, x));
            mesh.addColor(ofFloatColor(1.0));
        }
    }
    
    /// Shader
    string updatePosVert = STRINGIFY(
                                      uniform sampler2DRect sourceTex;
                                      uniform sampler2DRect colorTex;
                                     
                                      void main() {
                                          vec2 st = gl_MultiTexCoord0.st;

                                          vec3 pos = vec3(st.x, st.y, texture2DRect(sourceTex, st).b * 50.0);
                                          vec3 color = texture2DRect(colorTex, st).rgb;
                                          
                                          gl_FrontColor = vec4(color, 1.0);
                                          gl_PointSize = 1.0;
                                          gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);
                                      }
                                     );
    updatePosShader.setupShaderFromSource(GL_VERTEX_SHADER, updatePosVert);
    updatePosShader.linkProgram();

}

//--------------------------------------------------------------
void ofApp::update(){
    rd.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    cam.begin();
    ofPushStyle();
    
    ofTranslate(160, -80);
    ofRotateX(60);
    ofRotateZ(90);
    
    updatePosShader.begin();
    updatePosShader.setUniformTexture("sourceTex", rd.getSourceTexture(), 0);
    updatePosShader.setUniformTexture("colorTex", rd.getColorTexture(), 1);
    mesh.draw();
    updatePosShader.end();
    
    ofPopStyle();
    cam.end();
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
