#ifndef Sun_hpp
#define Sun_hpp

#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "macros.h"

#define SUN_RADIUS 3.0
#define SUN_ORBIT_RADIUS ENVIRONMENT_RADIUS - 50.0

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
    
    vec2 positionOnScreen;
    bool onScreen;
    
private:
    
    float speed = 0.1;
    
    float angle = 0.0;
    vec3 position = vec3( 0, 0, SUN_ORBIT_RADIUS );
};

#endif /* Sun_hpp */
