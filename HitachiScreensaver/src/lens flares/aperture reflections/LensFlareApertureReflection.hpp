#ifndef LensFlareApertureReflection_hpp
#define LensFlareApertureReflection_hpp

using namespace ci;
using namespace ci::app;

#include "macros.h"

#include "LensFlareElement.hpp"

class LensFlareApertureReflection: public LensFlareElement
{
    
public:
    
    LensFlareApertureReflection( std::string filename );
    
    void draw( vec2, vec2, bool, float, float ) override;
    
private:
    
    float calculateScale( float );
    
    gl::Texture2dRef texture;
};

#endif /* LensFlareApertureReflection_hpp */
