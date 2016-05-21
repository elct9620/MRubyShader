//
//  ofRuby3DSphere.cpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/21.
//
//

#include "ofRuby3DSphere.hpp"

const char* ofRuby3DSphere::NAME = "Sphere";

mrb_value ofRuby3DSphere::init(mrb_state *mrb, mrb_value self) {
    struct Primitive *primitive;
    primitive = (struct Primitive*) DATA_PTR(self);
    
    // Initialize Object, clear possiable exists data
    if(primitive) {
        free(mrb, primitive);
    }
    
    DATA_TYPE(self) = &ofRubySphereType;
    DATA_PTR(self) = NULL;
    
    primitive = alloc(mrb);
    primitive->instance = new ofSpherePrimitive();
    
    DATA_PTR(self) = primitive;
    
    // Initialize
    mrb_value radius;
    mrb_value position; // TODO: Implement Vector Object
    
    ofSpherePrimitive* instance = static_cast<ofSpherePrimitive*>(primitive->instance);
    
    int argc = mrb_get_argc(mrb);
    mrb_get_args(mrb, "|fo", &radius, &position);
    
    if(argc > 0) { // Radius given
        instance->setRadius(mrb_float(radius));
    }
    
    if(argc > 1) { // Position given
        // TODO: Implement position assign
    }
    
    
    return self;
}

void ofRuby3DSphere::setup(mrb_state *mrb, RClass *klass) {
    mrb_define_method(mrb, klass, "initialize", init, MRB_ARGS_OPT(2));
}