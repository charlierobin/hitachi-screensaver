#ifndef LensFlare_hpp
#define LensFlare_hpp

#include "cinder/ObjLoader.h"

#include "IItem.hpp"

using namespace ci;
using namespace ci::app;

class LensFlare: public IItem
{
    
public:
    
    LensFlare();
    
    void update( float, std::vector<IItem *>, int ) override;
    void draw( bool ) override;
    
    vec2 position;
    float intensity = 1.0;
    
private:
    
    gl::Texture2dRef texture;
};

#define SAMPLER_SIZE 5

#endif /* LensFlare_hpp */
