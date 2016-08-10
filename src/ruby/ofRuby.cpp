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
    load(sourceFile);
}

void ofRuby::load(ofFile file) {
    if(!file.exists()) {
        ofLog(ofLogLevel::OF_LOG_WARNING, "Ruby file not exists");
        return;
    }
    
    ofLog(ofLogLevel::OF_LOG_NOTICE, "Reading file: %s", file.path().c_str());
    
    ofBuffer sourceCode = file.readToBuffer();
    mrb_load_string(mrb, sourceCode.getData());
    
    checkError();
    file.close();
}

void ofRuby::loadDirectory(const std::string path) {
    ofDirectory sourceDirectory(ofToDataPath(path));
    
    if(!sourceDirectory.exists()) {
        ofLog(ofLogLevel::OF_LOG_WARNING, "Source directory not exists");
        return;
    }
    
    sourceDirectory.allowExt("rb");
    std::vector<ofFile> codes = sourceDirectory.getFiles();
    
    for(ofFile file : codes) {
        load(file.path());
    }
    sourceDirectory.close();
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

bool ofRuby::constDefined(const char* constName) {
    mrb_sym id(mrb_intern_cstr(mrb, constName));
    return mrb_const_defined(mrb, mrb_obj_value(mrb->object_class), id);
}

mrb_value ofRuby::newObject(const char *className) {
    RClass* klass = mrb_class_get(mrb, className);
    mrb_int argc = 0;
    return mrb_obj_new(mrb, klass, argc, NULL);
}


void ofRuby::checkError() {
    // Very simple error check by mrb->exc check
    
    if(mrb->exc) {
        mrb_value exception = mrb_obj_value(mrb->exc);
        string message(mrb_string_value_ptr(mrb, exception));
        ofLog(ofLogLevel::OF_LOG_ERROR, message);
    }
}