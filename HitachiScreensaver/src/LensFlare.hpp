#ifndef LensFlare_hpp
#define LensFlare_hpp

#include "cinder/ObjLoader.h"

using namespace ci;
using namespace ci::app;

class LensFlare
{

public:
    
    LensFlare();
    
    void draw();
    
    vec2 position;
    float intensity = 1.0;
    
private:
    
    gl::Texture2dRef texture;
};

#endif /* LensFlare_hpp */
