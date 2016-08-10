#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ruby = new ofRuby();
    
    // Add Built-in class
    ruby->loadClass<ofRuby3DPrimitive>();
    ruby->loadClassFrom<ofRuby3DSphere>("Primitive");
    ruby->loadClass<ofRubyVector2D>();
    ruby->loadClassFrom<ofRubyVector3D>("Vector2D");
    ruby->loadClass<ofRubyShader>();
    
    ruby->load("app.rb");
    if(ruby->constDefined("Application")) {
        appInstance = ruby->createObject("Application");
        ruby->call("setup", appInstance, 0, NULL);
    } else {
        ofSystemAlertDialog("The \"Application\" class is not exists.");
        ofExit();
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ruby->call("update", appInstance, 0, NULL);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ruby->call("draw", appInstance, 0, NULL);
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
