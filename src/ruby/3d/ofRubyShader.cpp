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
    
    stringstream vertexSrc;
    vertexSrc << "#version 150\n";
    vertexSrc << "uniform mat4 modelViewProjectionMatrix;\n";
    vertexSrc  << "in vec4 position;\n";
    vertexSrc  << "void main(void){\n";
    vertexSrc  << "\tgl_Position=modelViewProjectionMatrix*position;\n";
    vertexSrc  << "}\n";
    
    stringstream fragmentSrc;
    fragmentSrc << "#version 150\n";
    fragmentSrc << "out vec4 outputColor;\n";
    fragmentSrc << "void main(void) {\n";
    fragmentSrc << "\toutputColor = vec4(1, 0, 0, 1);\n";
    fragmentSrc << "}\n";

    shader->instance->setupShaderFromSource(GL_VERTEX_SHADER, vertexSrc.str());
    shader->instance->setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentSrc.str());
    shader->instance->bindDefaults();
    shader->instance->linkProgram();
    
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