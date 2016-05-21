//
//  ofRuby3DSphere.hpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/21.
//
//

#ifndef ofRuby3DSphere_hpp
#define ofRuby3DSphere_hpp

#include <stdio.h>

#include "ofRuby3DPrimitive.hpp"
#include "ofRubyVector3D.hpp"

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/class.h"

class ofRuby3DSphere : public ofRuby3DPrimitive {
    
public:
    
    static const char* NAME;
    
    static void setup(mrb_state* mrb, RClass* klass);
    
    static mrb_value init(mrb_state* mrb, mrb_value self);
};

static struct mrb_data_type ofRubySphereType = { "Sphere", ofRuby3DSphere::free };


#endif /* ofRuby3DSphere_hpp */
