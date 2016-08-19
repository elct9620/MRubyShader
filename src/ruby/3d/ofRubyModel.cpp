//
//  ofRubyModel.cpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/8/13.
//
//

#include "ofRubyModel.hpp"

const char* ofRubyModel::NAME = "Model";

void ofRubyModel::free(mrb_state *mrb, void *prt) {
    struct Model* model = static_cast<struct Model*>(prt);
    
    if(model != NULL) {
        ::free(model->instance);
    }
    
    mrb_free(mrb, prt);
}

ofRubyModel::Model* ofRubyModel::alloc(mrb_state *mrb) {
    struct Model* model;
    model = (struct Model*) mrb_alloca(mrb, sizeof(struct Model));
    return model;
}

void ofRubyModel::setup(mrb_state *mrb, RClass *klass) {
    mrb_define_method(mrb, klass, "initialize", init, MRB_ARGS_OPT(1));
    
    mrb_define_method(mrb, klass, "load", load, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, klass, "draw", draw, MRB_ARGS_NONE());
    mrb_define_method(mrb, klass, "position=", setPosition, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, klass, "rotation=", setRotation, MRB_ARGS_REQ(1));
}

mrb_value ofRubyModel::init(mrb_state* mrb, mrb_value self) {
    struct Model* model;
    model = (struct Model*) DATA_PTR(self);
    
    if(model) {
        free(mrb, model);
    }
    
    DATA_TYPE(self) = &ofRubyModelType;
    DATA_PTR(self) = NULL;
    
    model = alloc(mrb);
    model->instance = new ofxAssimpModelLoader;
    
    DATA_PTR(self) = model;
    
    if(mrb_get_argc(mrb) > 0) {
        load(mrb, self);
    }
    
    return self;
}

mrb_value ofRubyModel::load(mrb_state *mrb,  mrb_value self) {
    struct Model* model;
    model = (struct Model*) DATA_PTR(self);
    
    mrb_value modelPath;
    mrb_get_args(mrb, "S", &modelPath);
    
    std::string modelName(mrb_string_value_cstr(mrb, &modelPath));
    if(model->instance->loadModel(modelName)) {
        model->instance->disableMaterials(); // Disable default material to use custom shader
        return mrb_true_value();
    } else {
        return mrb_false_value();
    }
}

mrb_value ofRubyModel::draw(mrb_state* mrb, mrb_value self) {
    struct Model* model;
    model = (struct Model*) DATA_PTR(self);
    
    model->instance->drawFaces();
    
    return self;
}

mrb_value ofRubyModel::setPosition(mrb_state* mrb, mrb_value self) {
    struct Model* model;
    model = (struct Model*) DATA_PTR(self);
    
    mrb_value position;
    mrb_get_args(mrb, "o", &position);
    
    ofVec3f ofPosition = ofRuby3DPrimitive::getVector3DFromRuby(position);
    model->instance->setPosition(ofPosition.x, ofPosition.y, ofPosition.z);
    
    return self;
}

mrb_value ofRubyModel::setRotation(mrb_state* mrb, mrb_value self) {
    struct Model* model;
    model = (struct Model*) DATA_PTR(self);
    
    mrb_value rotation;
    mrb_get_args(mrb, "o", &rotation);
    
    ofVec3f ofRotation = ofRuby3DPrimitive::getVector3DFromRuby(rotation);
    model->instance->setRotation(0, ofRotation.x, 1, 0, 0);
    model->instance->setRotation(1, ofRotation.y, 0, 1, 0);
    model->instance->setRotation(2, ofRotation.z, 0, 0, 1);
    
    return self;
}