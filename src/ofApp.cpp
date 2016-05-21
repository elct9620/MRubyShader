#include "ofApp.h"

#include "ofRuby3DPrimitive.hpp"
#include "ofRuby3DSphere.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    ruby = new ofRuby();
    
    // Add Built-in class
    ruby->loadClass<ofRuby3DPrimitive>();
    ruby->loadClassFrom<ofRuby3DSphere>("Primitive");
    
    ruby->load("app.rb");
    
    ruby->call("setup");
}

//--------------------------------------------------------------
void ofApp::update(){
    ruby->call("update");
}

//--------------------------------------------------------------
void ofApp::draw(){
    ruby->call("draw");
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
