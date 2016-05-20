//
//  ofRuby.hpp
//  RubyShader
//
//  Created by 蒼時弦也 on 2016/5/20.
//
//

#ifndef ofRuby_hpp
#define ofRuby_hpp

#include <stdio.h>

#include "ofMain.h"
#include "ofRubyArgument.hpp"

#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/string.h"
#include "mruby/data.h"
#include "mruby/class.h"
#include "mruby/array.h"

class ofRuby {
public:
    ofRuby();
    ~ofRuby();
    
    void load(const std::string path);
    bool call(const char* methodName);
    bool call(const char* methodName, ofRubyArgument* arg);
    ofRubyArgument* buildArgument(int size) {
        return new ofRubyArgument(mrb, size);
    };
    
private:
    mrb_state* mrb;
};

#endif /* ofRuby_hpp */
