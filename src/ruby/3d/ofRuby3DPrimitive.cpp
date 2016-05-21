//
//  ofRuby3DPrimitive.cpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/21.
//
//

#include "ofRuby3DPrimitive.hpp"

const char* ofRuby3DPrimitive::NAME = "Primitive";

void ofRuby3DPrimitive::free(mrb_state *mrb, void *ptr) {
    
    Primitive *primitive = static_cast<Primitive*>(ptr);
    
    // If primitive exists, release of3DPrimitive memory
    if(primitive != NULL) {
        ::free(primitive->instance);
    }
    
    mrb_free(mrb, ptr);
}

struct ofRuby3DPrimitive::Primitive* ofRuby3DPrimitive::alloc(mrb_state *mrb) {
    Primitive* primitive;
    primitive = (struct Primitive*) mrb_alloca(mrb, sizeof(struct Primitive));
    
    // TODO: Initialize Primitive
    return primitive;
}

mrb_value ofRuby3DPrimitive::init(mrb_state *mrb, mrb_value self) {
    struct Primitive *primitive;
    primitive = (struct Primitive*) DATA_PTR(self);
    
    // Initialize Object, clear possiable exists data
    if(primitive) {
        free(mrb, primitive);
    }
    
    DATA_TYPE(self) = &ofRuby3DPrimitiveType;
    DATA_PTR(self) = NULL;
    
    primitive = alloc(mrb);
    primitive->instance = new of3dPrimitive();
     
    DATA_PTR(self) = primitive;
    return self;
}

void ofRuby3DPrimitive::setup(mrb_state *mrb, RClass *klass) {
    mrb_define_method(mrb, klass, "initialize", init, MRB_ARGS_NONE());
    
    mrb_define_method(mrb, klass, "draw", draw, MRB_ARGS_OPT(1));
}

// Instance Methods
mrb_value ofRuby3DPrimitive::draw(mrb_state *mrb, mrb_value self) {
    
    struct Primitive* primitive = (struct Primitive*) DATA_PTR(self);
    primitive->instance->draw();
    
    return self;
}