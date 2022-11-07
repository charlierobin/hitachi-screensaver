#ifndef Pyramid_hpp
#define Pyramid_hpp

#include "cinder/ObjLoader.h"
#include "cinder/Rand.h"

#include "macros.h"

#include "Tweening.hpp"

using namespace ci;
using namespace ci::app;

class Pyramid
{

public:
    
    Pyramid();
    Pyramid( vec3, vec3 );
    
    void update( float, std::vector<Pyramid *>, int );
    void draw();
    
    vec3 mPosition;
    
private:
    
    std::vector<gl::BatchRef> slices_;
    std::vector<gl::BatchRef> maskSlices;
    
    gl::BatchRef collisionSphere;
    
//    vec3 mPosition;
    vec3 speedPerSecond;
    
    float physicsRadius = 120;
    float physicsDiameter = ( physicsRadius * 0.1 ) * 2;
    
    bool flashing_ = false;
    int direction_ = 1;
    unsigned short current_ = 0;
    int counter_ = 0;
    
    short spinning_ = -1;
    float spinningCounter_ = 0;
    
    vec3 tumbleAxis_ = vec3( 1, 1, 0 );
    float tumbleSpeedPerSecond = 1.0;
    float tumbleAngle_ = 0.0;
    
    float THIRD_OF_A_TURN  = ONE_TURN / 3.0f;
};

#define FLASHING_COUNTER_MAX 3
#define SPIN_COUNTER_MAX 120

#endif /* Pyramid_hpp */
