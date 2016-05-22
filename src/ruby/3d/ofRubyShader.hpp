//
//  ofRubyShader.hpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/21.
//
//

#ifndef ofRubyShader_hpp
#define ofRubyShader_hpp

#include <stdio.h>

#include "ofMain.h"

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/class.h"
#include "mruby/string.h"

class ofRubyShader {
public:
    static const char* NAME;
    
    struct Shader {
        ofShader* instance;
    };
    
    static void setup(mrb_state* mrb, RClass* klass);
    
    static mrb_value init(mrb_state* mrb, mrb_value self);
    static void free(mrb_state* mrb, void *ptr);
    static struct Shader* alloc(mrb_state* mrb);
    
    // Instance method
    static mrb_value draw(mrb_state* mrb, mrb_value self);
    static mrb_value bind(mrb_state* mrb, mrb_value self);
    static mrb_value link(mrb_state* mrb, mrb_value slef);
    static mrb_value setVertexShader(mrb_state* mrb, mrb_value self);
    static mrb_value setFragmentShader(mrb_state* mrb, mrb_value self);
    
    // Helper Method
    
    
};

static struct mrb_data_type ofRubyShaderType = { "Shader", ofRubyShader::free };

#endif /* ofRubyShader_hpp */
