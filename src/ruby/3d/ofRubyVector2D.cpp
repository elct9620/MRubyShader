//
//  ofRubyVector2D.cpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/21.
//
//

#include "ofRubyVector2D.hpp"

const char* ofRubyVector2D::NAME = "Vector2D";

void ofRubyVector2D::free(mrb_state* mrb, void *ptr) {
    mrb_free(mrb, ptr);
}

struct ofRubyVector2D::Vector* ofRubyVector2D::alloc(mrb_state *mrb) {
    Vector* vector;
    vector = (Vector*) mrb_alloca(mrb, sizeof(Vector));
    return vector;
}

void ofRubyVector2D::setup(mrb_state *mrb, RClass *klass) {
    mrb_define_method(mrb, klass, "initialize", init, MRB_ARGS_REQ(2));
}

mrb_value ofRubyVector2D::init(mrb_state *mrb, mrb_value self) {
    
    struct Vector* vector;
    vector = (struct Vector*) DATA_PTR(self);
    
    if(vector) {
        free(mrb, vector);
    }
    
    DATA_TYPE(self) = &ofRubyVector2DType;
    DATA_PTR(self) = NULL;
    
    vector = alloc(mrb);
    
    DATA_PTR(self) = vector;
    
    // Initialize
    mrb_value x;
    mrb_value y;
    
    mrb_get_args(mrb, "ff", &x, &y);
    
    vector->x = mrb_float(x);
    vector->y = mrb_float(y);
    
    return self;
}