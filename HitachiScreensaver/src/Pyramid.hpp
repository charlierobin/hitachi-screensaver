#ifndef Pyramid_hpp
#define Pyramid_hpp

#include "cinder/ObjLoader.h"
#include "cinder/Rand.h"
#include "cinder/Timeline.h"

#include "macros.h"
#include "Tweening.hpp"

using namespace ci;
using namespace ci::app;

class Pyramid
{

public:
    
    Pyramid();
//    Pyramid( vec3, vec3 );
    Pyramid( float, vec3, vec3, vec3, vec3 );
    
    void update( float, CameraPersp );
    void update( float, vec3, vec3, vec3, vec3 );
    void draw();
    
private:
    
    void start();
    
    std::vector<gl::BatchRef> slices;

    vec3 mPosition = vec3( 0, 0, 500 );
    vec3 speedPerSecond = vec3( 0, 0, 0 );
    
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
    
    float margin;
    
    vec3 topLeftNear;
    vec3 bottomRightNear;
    vec3 topLeftFar;
    vec3 bottomRightFar;
    
    CueRef cue;
    bool active = false;
    bool activated = false;
};

#define FLASHING_COUNTER_MAX 3
#define SPIN_COUNTER_MAX 120

#define MARGIN_DEFAULT 40.0

#endif /* Pyramid_hpp */
