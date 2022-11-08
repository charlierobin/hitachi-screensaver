#ifndef Starfield_hpp
#define Starfield_hpp

#include "cinder/ObjLoader.h"
#include "cinder/Rand.h"
#include "glm/gtc/random.hpp"

#include "macros.h"

using namespace ci;
using namespace ci::app;

class Starfield
{

public:
    
    Starfield();
    
    void update( float );
    void draw();
    
private:
    
    float angle = 0.0f;
    vec3 rotationAxis = vec3( 0, 1, 0 );
    
    float rotationSpeedPerSecond = ONE_TURN / 120;
    
    gl::BatchRef topSection;
    gl::BatchRef bottomSection;
    gl::BatchRef leftSection;
    gl::BatchRef rightSection;
    gl::BatchRef frontSection;
    gl::BatchRef backSection;
    
    gl::TextureRef topTexture;
    gl::TextureRef bottomTexture;
    gl::TextureRef leftTexture;
    gl::TextureRef rightTexture;
    gl::TextureRef frontTexture;
    gl::TextureRef backTexture;
    
    gl::TextureRef twinkleTexture;
    
    struct starData
    {
        int step;
        int direction;
        float rotationX;
        float rotationY;
        float rotationZ;
        float rotationZDelta;
        Color colour;
    };
    
    std::vector<starData> stars;
    std::vector<gl::BatchRef> starBatches;
};

#define NUMBER_OF_STARS 200
#define MAX_TWINKLE_FRAMES 64

#define STAR_SIZE 20

#endif /* Starfield_hpp */

