#ifndef Placard_hpp
#define Placard_hpp

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/ObjLoader.h"

#include "cinder/Rand.h"

#include "macros.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Placard
{
    
public:
    
    Placard();
    Placard( string );
    
    void update( float );
    void draw();
    
private:
    
    gl::BatchRef placard_;
    
    float angle_ = 0.0;
    float speedPerSecond_ = ONE_TURN / 20;
    
    float zRotation_ = 0.0f;
    float yRotation_ = 0.0f;
    
    gl::Texture2dRef texture_;
};

#endif /* Placard_hpp */
