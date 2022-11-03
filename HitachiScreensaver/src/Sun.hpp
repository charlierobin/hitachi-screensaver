#ifndef Sun_hpp
#define Sun_hpp

#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "macros.h"

#define SUN_RADIUS 5.0f
#define SUN_ORBIT_RADIUS ENVIRONMENT_RADIUS - 50.0f

#define AROUND_X_AXIS cinder::vec3( 1, 0, 0 )
#define AROUND_Y_AXIS cinder::vec3( 0, 1, 0 )
#define AROUND_Z_AXIS cinder::vec3( 0, 0, 1 )

using namespace ci;
using namespace ci::app;

class Sun
{
    
public:
    
    void update( float, CameraPersp );
    void draw();
    
    bool isOnScreen();
    
    float sunAngle_ = 0.0f;
    
    vec3 sunPosition_ = vec3( 0.0f, 0.0f, SUN_ORBIT_RADIUS );
    vec2 sunPositionOnScreen_;
    
    float speed = 0.5;
};

#endif /* Sun_hpp */
