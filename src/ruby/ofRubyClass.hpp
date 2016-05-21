//
//  ofRubyClass.hpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/21.
//
//

#ifndef ofRubyClass_hpp
#define ofRubyClass_hpp

#include <stdio.h>

#include "ofMain.h"

#include "mruby.h"
#include "mruby/class.h"

typedef mrb_value (*RubyMethod) (mrb_state*, mrb_value);

class ofRubyClass {
public:
    ofRubyClass(mrb_state* mrb, const char* name): mrb(mrb) {
        klass = mrb_define_class(mrb, name, mrb->object_class);
    };
    
    ofRubyClass(mrb_state* mrb, const char* name, RClass* parent): mrb(mrb) {
        klass = mrb_define_class(mrb, name, parent);
    };
    
    ~ofRubyClass() {
        // TODO: RClass* will release or not?
    };
    
    void setInitMethod(RubyMethod method);
    void addMethod(const char* name, RubyMethod method, int argc);
    
    RClass* getClass() {
        return klass;
    };
    
private:
    mrb_state* mrb;
    struct RClass* klass;
};

#endif /* ofRubyClass_hpp */
