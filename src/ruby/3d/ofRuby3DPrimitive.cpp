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
    mrb_define_method(mrb, klass, "move", move, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, klass, "x", getX, MRB_ARGS_NONE());
    mrb_define_method(mrb, klass, "y", getX, MRB_ARGS_NONE());
    mrb_define_method(mrb, klass, "z", getX, MRB_ARGS_NONE());
    mrb_define_method(mrb, klass, "position=", setPosition, MRB_ARGS_REQ(1));
}

// Instance Methods
mrb_value ofRuby3DPrimitive::draw(mrb_state *mrb, mrb_value self) {
    
    struct Primitive* primitive = (struct Primitive*) DATA_PTR(self);
    primitive->instance->draw();
    
    return self;
}

mrb_value ofRuby3DPrimitive::move(mrb_state *mrb, mrb_value self) {
    Primitive* primivite;
    primivite = (Primitive*) DATA_PTR(self);
    
    mrb_value offset;
    mrb_get_args(mrb, "o", &offset);
    
    primivite->instance->move(getVector3DFromRuby(offset));
    return self;
}

mrb_value ofRuby3DPrimitive::getX(mrb_state* mrb, mrb_value self) {
    Primitive* primivite;
    primivite = (Primitive*) DATA_PTR(self);
    return mrb_float_value(mrb, primivite->instance->getX());
}

mrb_value ofRuby3DPrimitive::getY(mrb_state* mrb, mrb_value self) {
    Primitive* primivite;
    primivite = (Primitive*) DATA_PTR(self);
    return mrb_float_value(mrb, primivite->instance->getY());
}

mrb_value ofRuby3DPrimitive::getZ(mrb_state* mrb, mrb_value self) {
    Primitive* primivite;
    primivite = (Primitive*) DATA_PTR(self);
    return mrb_float_value(mrb, primivite->instance->getZ());
}


mrb_value ofRuby3DPrimitive::setPosition(mrb_state *mrb, mrb_value self) {
    
    // TODO: Support Vector and pure float both
    
    Primitive* primitive;
    primitive = (Primitive*) DATA_PTR(self);
    
    mrb_value newPosition;
    mrb_get_args(mrb, "o", &newPosition);
    
    ofVec3f ofPosition = getVector3DFromRuby(newPosition);
    primitive->instance->setPosition(ofPosition.x, ofPosition.y, ofPosition.z);
    return self;
}

// Helper Method
ofVec3f ofRuby3DPrimitive::getVector3DFromRuby(mrb_value object) {
    const mrb_data_type* type = DATA_TYPE(object);
    string typeName(type->struct_name);
    ofVec3f vector(0, 0, 0);
    
    
    // FIX: Data Type pointer not same as DATA_TYPE(object) pointer
    if(typeName == "Vector2D") {
        ofRubyVector2D::Vector* data;
        data = (ofRubyVector2D::Vector*) DATA_PTR(object);
        vector.x = data->x;
        vector.y = data->y;
    }
    
    if(typeName == "Vector3D") {
        ofRubyVector3D::Vector* data;
        data = (ofRubyVector3D::Vector*) DATA_PTR(object);
        vector.x = data->x;
        vector.y = data->y;
        vector.z = data->z;
    }
    
    return vector;
    
}