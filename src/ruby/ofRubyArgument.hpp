//
//  ofRubyArgument.hpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/20.
//
//

#ifndef ofRubyArgument_hpp
#define ofRubyArgument_hpp

#include <stdio.h>

#include "mruby.h"
#include "mruby/array.h"

class ofRubyArgument {
public:
    ofRubyArgument(mrb_state* mrb, int size): mrb(mrb), size(size), argc(0) {
        // TODO: Specify size will speed up running?
        args = new mrb_value[size];
    };
    ~ofRubyArgument() {
        delete[] args;
    };
    
    void push(mrb_value value);
    void push(int value);
    void push(float value);
    void push(double value);
    void push(const char* value);
    
    mrb_value* getArgument();
    int getArgumentCount() {
        return argc;
    };
    
private:
    mrb_state* mrb;
    mrb_value* args;
    int size;
    int argc = 0;
};

#endif /* ofRubyArgument_hpp */
