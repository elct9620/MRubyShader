#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSeparateSpecularLight();
    ofEnableDepthTest();
    ofEnableNormalizedTexCoords();
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    
    ruby = new ofRuby();
    
    light.enable();
    
    // Add Built-in class
    ruby->loadClass<ofRuby3DPrimitive>();
    ruby->loadClassFrom<ofRuby3DSphere>("Primitive");
    ruby->loadClass<ofRubyVector2D>();
    ruby->loadClassFrom<ofRubyVector3D>("Vector2D");
    ruby->loadClass<ofRubyShader>();
    ruby->loadClass<ofRubyModel>();
    ruby->loadClass<ofRubyTexture>();
    
    ruby->load("lib/shader.rb");
    ruby->load("app.rb");
    if(ruby->constDefined("Application")) {
        appInstance = ruby->newObject("Application");
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
    //ofClear(0);
    ruby->call("draw", appInstance, 0, NULL);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofRubyArgument *args = ruby->buildArgument(1);
    args->push(key);
    ruby->call("on_key_down", appInstance, 1, args->getValues());
    delete args;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    ofRubyArgument *args = ruby->buildArgument(1);
    args->push(key);
    ruby->call("on_key_up", appInstance, 1, args->getValues());
    delete args;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    ofRubyArgument *args = ruby->buildArgument(2);
    args->push(x);
    args->push(y);
    ruby->call("on_mouse_moved", appInstance, 2, args->getValues());
    delete args;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    ofRubyArgument *args = ruby->buildArgument(3);
    args->push(x);
    args->push(y);
    args->push(button);
    ruby->call("on_mouse_dragged", appInstance, 3, args->getValues());
    delete args;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofRubyArgument *args = ruby->buildArgument(3);
    args->push(x);
    args->push(y);
    args->push(button);
    ruby->call("on_mouse_pressed", appInstance, 3, args->getValues());
    delete args;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ofRubyArgument *args = ruby->buildArgument(3);
    args->push(x);
    args->push(y);
    args->push(button);
    ruby->call("on_mouse_released", appInstance, 3, args->getValues());
    delete args;
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
