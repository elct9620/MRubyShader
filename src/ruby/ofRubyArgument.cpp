//
//  ofRubyArgument.cpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/20.
//
//

#include "ofRubyArgument.hpp"

void ofRubyArgument::push(mrb_value value) {
    
    if(argc >= size) {
        return; // Reach max size of argument
    }
    
    args[argc] = value;
    argc++;
}

void ofRubyArgument::push(int value) {
    push(mrb_fixnum_value(value));
}

void ofRubyArgument::push(float value) {
    push(mrb_float_value(mrb, value));
}

void ofRubyArgument::push(double value) {
    push(mrb_float_value(mrb, value));
}

void ofRubyArgument::push(const char *value) {
    push(mrb_str_new_cstr(mrb, value));
}