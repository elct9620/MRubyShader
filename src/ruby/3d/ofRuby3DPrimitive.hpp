//
//  ofRuby3DPrimitive.hpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/21.
//
//

#ifndef ofRuby3DPrimitive_hpp
#define ofRuby3DPrimitive_hpp

#include <stdio.h>

#include "ofMain.h"

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/class.h"

class ofRuby3DPrimitive {
    
public:
    
    static const char* NAME;
    
    struct Primitive {
        of3dPrimitive* instance;
    };
    
    static void setup(mrb_state* mrb, RClass* klass);
    
    static mrb_value init(mrb_state* mrb, mrb_value self);
    static void free(mrb_state* mrb, void *ptr);
    static struct Primitive* alloc(mrb_state* mrb);
    
    // Instance method
    static mrb_value draw(mrb_state* mrb, mrb_value self);
};

static struct mrb_data_type ofRuby3DPrimitiveType = { "Primitive", ofRuby3DPrimitive::free };

#endif /* ofRuby3DPrimitive_hpp */
