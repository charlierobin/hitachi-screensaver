#ifndef Starfield_hpp
#define Starfield_hpp

#include "cinder/ObjLoader.h"
#include "cinder/Rand.h"

#include "macros.h"

#include "IItem.hpp"

using namespace ci;
using namespace ci::app;

class Starfield: public IItem
{
public:
    
    Starfield();
    void update( float ) override;
    void draw() override;
    
private:
    
    float angle = 0.0f;
    vec3 rotationAxis = vec3( 0, 1, 0 );
    
    float rotationSpeedPerSecond = ONE_TURN / 120.0f;
    
    cinder::gl::BatchRef topSection;
    cinder::gl::BatchRef bottomSection;
    cinder::gl::BatchRef leftSection;
    cinder::gl::BatchRef rightSection;
    cinder::gl::BatchRef frontSection;
    cinder::gl::BatchRef backSection;
    
    gl::TextureRef topTexture;
    gl::TextureRef bottomTexture;
    gl::TextureRef leftTexture;
    gl::TextureRef rightTexture;
    gl::TextureRef frontTexture;
    gl::TextureRef backTexture;
};

#endif /* Starfield_hpp */
