#ifndef HeroPyramid_hpp
#define HeroPyramid_hpp

#include "macros.h"

#include "cinder/Rand.h"
#include "cinder/Timeline.h"

#include "HeroPyramidSlice.hpp"

using namespace ci;
using namespace ci::app;

class HeroPyramid
{
    
public:
    
    HeroPyramid();
    
    void update( float );
    void draw();
    
    void startComingIn();
    
private:
    
    float x_ = 0.0f;
    float y_ = 0.0f;
    float z_ = 0.0f;
    
    std::vector<HeroPyramidSlice *> slices_;
    
    float randomZRotation_ = 0.0f;
    float angle_ = 0.0f;
    
    gl::TextureRef mTexture;
    
    bool cued_ = false;
};

#define AROUND_Z_AXIS cinder::vec3( 0, 0, 1 )

#endif /* HeroPyramid_hpp */
