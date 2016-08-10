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

#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/string.h"
#include "mruby/data.h"
#include "mruby/class.h"
#include "mruby/array.h"
#include "mruby/variable.h"

// Headers --- BEGIN

#include "ofRubyArgument.hpp"
#include "ofRuby3DPrimitive.hpp"
#include "ofRuby3DSphere.hpp"
#include "ofRubyVector2D.hpp"
#include "ofRubyVector3D.hpp"
#include "ofRubyShader.hpp"

// Headers --- END

class ofRuby {
public:
    ofRuby();
    ~ofRuby();
    
    void load(const std::string path);
    void load(ofFile file);
    void loadDirectory(const std::string path);
    bool call(const char* methodName);
    bool call(const char* methodName, ofRubyArgument* arg);
    bool call(const char* methodName, mrb_value context, int argc, mrb_value* argv);
    bool constDefined(const char* constName);
    mrb_value newObject(const char* className);
    
    ofRubyArgument* buildArgument(int size) {
        return new ofRubyArgument(mrb, size);
    };
    
    template<class T>
    void loadClass() {
        loadClassFrom<T>(NULL);
    };
    
    template<class T>
    void loadClassFrom(const char* superClassName){
        if(classes[T::NAME] != NULL) {
            ofLog(ofLogLevel::OF_LOG_ERROR, "Class already loaded");
            return;
        }
        
        RClass* superClass = classes[superClassName];
        if(superClass == NULL) {
            superClass = mrb->object_class;
        }
        
        RClass* klass = mrb_define_class(mrb, T::NAME, superClass);
        T::setup(mrb, klass);
        
        ofLog(ofLogLevel::OF_LOG_NOTICE, "Class %s loaded, with super class %s", T::NAME, mrb_class_name(mrb, superClass));
        
        classes[T::NAME] = klass;
    };
    
private:
    mrb_state* mrb;
    
    void checkError();
    std::map<const char*, RClass*> classes;
};

#endif /* ofRuby_hpp */
