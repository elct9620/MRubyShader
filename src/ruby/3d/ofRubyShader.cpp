//
//  ofRubyShader.cpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/21.
//
//

#include "ofRubyShader.hpp"

const char* ofRubyShader::NAME = "Shader";

void ofRubyShader::free(mrb_state *mrb, void *ptr) {
    Shader* shader = static_cast<Shader*>(ptr);
    
    if(shader != NULL) {
        ::free(shader->instance);
    }
    
    mrb_free(mrb, ptr);
}

struct ofRubyShader::Shader* ofRubyShader::alloc(mrb_state *mrb) {
    struct Shader* shader;
    shader = (struct Shader*) mrb_alloca(mrb, sizeof(struct Shader));
    return shader;
}

void ofRubyShader::setup(mrb_state *mrb, RClass *klass) {
    mrb_define_method(mrb, klass, "initialize", init, MRB_ARGS_NONE());
    
    mrb_define_method(mrb, klass, "draw", draw, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, klass, "vertex=", setVertexShader, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, klass, "fragment=", setFragmentShader, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, klass, "bind", bind, MRB_ARGS_OPT(3));
    mrb_define_method(mrb, klass, "apply", apply, MRB_ARGS_NONE());
}

mrb_value ofRubyShader::init(mrb_state *mrb, mrb_value self) {
    struct Shader *shader;
    shader = (struct Shader*) DATA_PTR(self);
    
    if(shader) {
        free(mrb, shader);
    }
    
    
    
    DATA_TYPE(self) = &ofRubyShaderType;
    DATA_PTR(self) = NULL;
    
    shader = alloc(mrb);
    shader->instance = new ofShader();
    
    DATA_PTR(self) = shader;
    
    return self;
}

mrb_value ofRubyShader::draw(mrb_state *mrb, mrb_value self) {
    Shader* shader;
    shader = (Shader*) DATA_PTR(self);
    
    mrb_value block;
    mrb_get_args(mrb, "&", &block);
    
    shader->instance->begin();
    
    mrb_funcall(mrb, block, "call", 0); // Call block
    shader->instance->end();
    
    return self;
}

mrb_value ofRubyShader::bind(mrb_state* mrb, mrb_value self) {
    Shader* shader;
    shader = (Shader*) DATA_PTR(self);
    
    shader->instance->bindDefaults();
    
    return self;
}

mrb_value ofRubyShader::apply(mrb_state* mrb, mrb_value self) {
    Shader* shader;
    shader = (Shader*) DATA_PTR(self);
    
    shader->instance->linkProgram();
    
    return self;
}

mrb_value ofRubyShader::setVertexShader(mrb_state *mrb, mrb_value self) {
    Shader* shader;
    shader = (Shader*) DATA_PTR(self);
    
    mrb_value shaderValue;
    mrb_get_args(mrb, "S", &shaderValue);
    string shaderCode(mrb_string_value_ptr(mrb, shaderValue));
    
    shader->instance->setupShaderFromSource(GL_VERTEX_SHADER, shaderCode);
    
    return self;
}

mrb_value ofRubyShader::setFragmentShader(mrb_state *mrb, mrb_value self) {
    Shader* shader;
    shader = (Shader*) DATA_PTR(self);
    
    mrb_value shaderValue;
    mrb_get_args(mrb, "S", &shaderValue);
    string shaderCode(mrb_string_value_ptr(mrb, shaderValue));
    
    shader->instance->setupShaderFromSource(GL_FRAGMENT_SHADER, shaderCode);
    
    return self;
}