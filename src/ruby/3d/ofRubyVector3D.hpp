//
//  ofRubyVector3D.hpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/21.
//
//

#ifndef ofRubyVector3D_hpp
#define ofRubyVector3D_hpp

#include <stdio.h>

#include "ofMain.h"

#include "ofRubyVector2D.hpp"

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/class.h"

class ofRubyVector3D : public ofRubyVector2D {
    
public:
    
    static const char* NAME;
    
    struct Vector : ofRubyVector2D::Vector {
        float z;
    };
    
    static void setup(mrb_state* mrb, RClass* klass);
    
    static mrb_value init(mrb_state* mrb, mrb_value self);
    static struct Vector* alloc(mrb_state* mrb);
    
    // Class Method
    static mrb_value getZ(mrb_state* mrb, mrb_value self);
    static mrb_value add(mrb_state* mrb, mrb_value self);
};


static struct mrb_data_type ofRubyVector3DType = { "Vector3D", ofRubyVector3D::free };

#endif /* ofRubyVector3D_hpp */
