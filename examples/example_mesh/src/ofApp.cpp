#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);

    /*
     ofEasyCam
     */
    cam.setupPerspective(true, 60, 10, 0, ofVec2f(0.0, 0.3));
    cam.setDistance(300);
    cam.tilt(-10);

    /*
     ofxReactionDiffusion
     */
    scale = 3.0;
    
    rd.allocate(ofGetWidth(), ofGetHeight(), scale);
    rd.setPasses(0.998265);
    rd.setGrayScottParams(0.0239133, 0.0501276, 0.178571, 0.212041);
    
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
    string updatePosVert = STRINGIFY(
                                      uniform float width;
                                      uniform float height;
                                      uniform sampler2DRect sourceTex;
                                      uniform sampler2DRect colorTex;
                                     
                                      void main() {
                                          vec2 st = gl_MultiTexCoord0.st;

                                          vec3 pos = vec3(st.x - width/2.0, st.y - height/2.0, texture2DRect(sourceTex, st).b * 50.0);
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
    ofPushStyle();
    cam.begin();
    
    updatePosShader.begin();
    updatePosShader.setUniformTexture("sourceTex", rd.getSourceTexture(), 0);
    updatePosShader.setUniformTexture("colorTex", rd.getColorTexture(), 1);
    updatePosShader.setUniform1f("width", ofGetWidth()/scale);
    updatePosShader.setUniform1f("height", ofGetHeight()/scale);
    mesh.draw();
    updatePosShader.end();
    
    cam.end();
    ofPopStyle();
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
