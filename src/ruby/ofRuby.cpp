//
//  ofRuby.cpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/20.
//
//

#include "ofRuby.hpp"

ofRuby::ofRuby() {
    // Initialize MRuby
    mrb = mrb_open();
}

ofRuby::~ofRuby() {
    mrb_close(mrb);
}

void ofRuby::load(const std::string path) {
    ofFile sourceFile(ofToDataPath(path));
    
    if(!sourceFile.exists()) {
        ofLog(ofLogLevel::OF_LOG_WARNING, "Ruby file not exists");
        return;
    }
    
    ofBuffer sourceCode = sourceFile.readToBuffer();
    mrb_load_string(mrb, sourceCode.getData());
    
    if(mrb->exc) {
        // TODO: Handle Exception
    }
    
    sourceFile.close();
}

bool ofRuby::call(const char* methodName) {
    mrb_funcall(mrb, mrb_top_self(mrb), methodName, 0);
}

bool ofRuby::call(const char* methodName, ofRubyArgument* arg) {
    mrb_sym symbol(mrb_intern_cstr(mrb, methodName));
    mrb_funcall_argv(mrb, mrb_top_self(mrb), symbol, arg->getArgumentCount(), arg->getArgument());
}