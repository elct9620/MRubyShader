//
//  ofRubyTexture.hpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/8/30.
//
//

#ifndef ofRubyTexture_hpp
#define ofRubyTexture_hpp

#include <stdio.h>

#include "ofMain.h"

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/class.h"
#include "mruby/string.h"

class ofRubyTexture {
    
public:
    
    static const char* NAME;
    
    struct Texture {
        ofImage* instance;
    };
    
    static void setup(mrb_state* mrb, RClass* klass);
    
    static mrb_value init(mrb_state* mrb, mrb_value self);
    static struct Texture* alloc(mrb_state* mrb);
    static void free(mrb_state* mrb, void* ptr);
};


static struct mrb_data_type ofRubyTextureType = { "Texture", ofRubyTexture::free };

#endif /* ofRubyTexture_hpp */
