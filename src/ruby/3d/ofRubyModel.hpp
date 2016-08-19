//
//  ofRubyModel.hpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/8/13.
//
//

#ifndef ofRubyModel_hpp
#define ofRubyModel_hpp

#include <stdio.h>

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/class.h"
#include "mruby/string.h"

#include "ofRuby3DPrimitive.hpp"


class ofRubyModel {
    
public:
    static const char* NAME;
    
    struct Model {
        ofxAssimpModelLoader* instance;
    };
    
    static void setup(mrb_state* mrb, RClass* klass);
    
    static mrb_value init(mrb_state* mrb, mrb_value self);
    static void free(mrb_state* mrb, void* prt);
    static struct Model* alloc(mrb_state* mrb);
    
    static mrb_value load(mrb_state* mrb, mrb_value self);
    static mrb_value draw(mrb_state* mrb, mrb_value self);
    static mrb_value setPosition(mrb_state* mrb, mrb_value self);
    static mrb_value setRotation(mrb_state* mrb, mrb_value self);
};

static struct mrb_data_type ofRubyModelType { "Model", ofRubyModel::free };

#endif /* ofRubyModel_hpp */
