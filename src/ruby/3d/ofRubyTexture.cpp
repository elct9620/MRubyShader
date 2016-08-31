//
//  ofRubyTexture.cpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/8/30.
//
//

#include "ofRubyTexture.hpp"

const char* ofRubyTexture::NAME = "Texture";

void ofRubyTexture::setup(mrb_state *mrb, RClass* klass) {
    mrb_define_method(mrb, klass, "initialize", init, MRB_ARGS_REQ(1));
}

mrb_value ofRubyTexture::init(mrb_state *mrb, mrb_value self) {
    Texture* texture = (Texture*) DATA_PTR(self);
    
    if(texture) {
        free(mrb, texture);
    }
    
    DATA_TYPE(self) = &ofRubyTextureType;
    DATA_PTR(self) = NULL;
    
    texture = alloc(mrb);
    texture->instance = new ofImage;
    
    DATA_PTR(self) = texture;
    
    mrb_value path;
    mrb_get_args(mrb, "S", &path);
    
    string samplerImage(mrb_string_value_ptr(mrb, path));
    texture->instance->load(samplerImage);
    
    return self;
}

ofRubyTexture::Texture* ofRubyTexture::alloc(mrb_state *mrb) {
    struct Texture* texture;
    texture = (struct Texture*) mrb_alloca(mrb, sizeof(struct Texture));
    return texture;
}

void ofRubyTexture::free(mrb_state *mrb, void *ptr) {
    struct Texture* texture = static_cast<struct Texture*>(ptr);
    
    if(texture != NULL) {
        ::free(texture->instance);
    }
    
    mrb_free(mrb, ptr);
}