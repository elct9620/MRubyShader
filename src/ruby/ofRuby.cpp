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
    call(methodName, mrb_top_self(mrb), 0, NULL);
}

bool ofRuby::call(const char* methodName, ofRubyArgument* arg) {
    call(methodName, mrb_top_self(mrb), arg->getCount(), arg->getValues());
}

bool ofRuby::call(const char* methodName, mrb_value context, int argc, mrb_value* argv) {
    mrb_sym symbol(mrb_intern_cstr(mrb, methodName));
    mrb_funcall_argv(mrb, context, symbol, argc, argv);
    checkError();
}

void ofRuby::checkError() {
    // Very simple error check by mrb->exc check
    
    if(mrb->exc) {
        mrb_value exception = mrb_obj_value(mrb->exc);
        string message(mrb_string_value_ptr(mrb, exception));
        ofLog(ofLogLevel::OF_LOG_ERROR, message);
    }
}