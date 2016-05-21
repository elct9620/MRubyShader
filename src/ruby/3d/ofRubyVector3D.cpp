//
//  ofRubyVector3D.cpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/21.
//
//

#include "ofRubyVector3D.hpp"

const char* ofRubyVector3D::NAME = "Vector3D";

struct ofRubyVector3D::Vector* ofRubyVector3D::alloc(mrb_state *mrb) {
    Vector* vector;
    vector = (Vector*) mrb_alloca(mrb, sizeof(Vector));
    return vector;
}

mrb_value ofRubyVector3D::init(mrb_state *mrb, mrb_value self) {
    
    struct Vector* vector;
    vector = (struct Vector*) DATA_PTR(self);
    
    if(vector) {
        free(mrb, vector);
    }
    
    DATA_TYPE(self) = &ofRubyVector3DType;
    DATA_PTR(self) = NULL;
    
    vector = alloc(mrb);
    
    DATA_PTR(self) = vector;
    
    // Initialize
    mrb_value x;
    mrb_value y;
    mrb_value z;
    
    mrb_get_args(mrb, "fff", &x, &y, &z);
    
    vector->x = mrb_float(x);
    vector->y = mrb_float(y);
    vector->z = mrb_float(z);
    
    return self;
}

void ofRubyVector3D::setup(mrb_state *mrb, RClass *klass) {
    mrb_define_method(mrb, klass, "initialize", init, MRB_ARGS_REQ(3));
    
    mrb_define_method(mrb, klass, "z", getZ, MRB_ARGS_NONE());
}

mrb_value ofRubyVector3D::getZ(mrb_state *mrb, mrb_value self) {
    Vector* vector;
    vector = (Vector*) DATA_PTR(self);
    return mrb_float_value(mrb, vector->z);
}
