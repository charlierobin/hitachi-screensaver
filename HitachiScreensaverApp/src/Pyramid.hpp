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
    
    void update( float, CameraPersp );
    void update( Frustum f );
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
    
    Frustum f;
    
    CueRef cue;
    bool active = false;
    bool activated = false;
    
    Color red = Color( 0.937254901960784, 0.105882352941176, 0.203921568627451 );
    
//    gl::BatchRef testSphere;
    
    enum direction {
        left, right, top, bottom,
        last
    };
};

#define FLASHING_COUNTER_MAX 3
#define SPIN_COUNTER_MAX 120

#define PROBE_STEP 3

#endif /* Pyramid_hpp */
