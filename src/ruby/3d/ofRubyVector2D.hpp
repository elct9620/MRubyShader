//
//  ofRubyVector2D.hpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/21.
//
//

#ifndef ofRubyVector2D_hpp
#define ofRubyVector2D_hpp

#include <stdio.h>

#include "ofMain.h"

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/class.h"

class ofRubyVector2D {
    
public:
    
    static const char* NAME;
    
    struct Vector {
        float x;
        float y;
    };
    
    static void setup(mrb_state* mrb, RClass* klass);
    
    static mrb_value init(mrb_state* mrb, mrb_value self);
    static void free(mrb_state* mrb, void *ptr);
    static struct Vector* alloc(mrb_state* mrb);
    
    // Class Method
    static mrb_value add(mrb_state* mrb, mrb_value self);
    static mrb_value getX(mrb_state* mrb, mrb_value self);
    static mrb_value getY(mrb_state* mrb, mrb_value self);
};

static struct mrb_data_type ofRubyVector2DType = { "Vector2D", ofRubyVector2D::free };

#endif /* ofRubyVector2D_hpp */
