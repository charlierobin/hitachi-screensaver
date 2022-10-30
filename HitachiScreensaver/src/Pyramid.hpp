#ifndef Pyramid_hpp
#define Pyramid_hpp

#include "cinder/ObjLoader.h"
#include "cinder/Rand.h"

#include "macros.h"

#include "IItem.hpp"
#include "Tweening.hpp"

using namespace ci;
using namespace ci::app;

class Pyramid: public IItem
{
    
public:
    
    Pyramid();
    
    void update( float ) override;
    void draw() override;
    
private:
    
    std::vector<gl::BatchRef> slices_;
//    int vectorSize_;
    
    bool flashing_ = false;
    int direction_ = 1;
    unsigned short current_ = 0;
    int counter_ = 0;
    
    short spinning_ = -1;
    float spinningCounter_ = 0;
    
    vec3 mPosition;
    vec3 speedPerSecond;
    
    vec3 tumbleAxis_ = vec3( 0, 1, 0 );
    float tumbleSpeed_ = 0.0;
    float tumbleAngle_ = 0.0;
    
    float THIRD_OF_A_TURN  = ONE_TURN / 3.0f;
};

#define FLASHING_COUNTER_MAX 3
#define SPIN_COUNTER_MAX 120

#endif /* Pyramid_hpp */
