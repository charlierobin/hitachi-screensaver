#ifndef LensFlareApertureReflection_hpp
#define LensFlareApertureReflection_hpp

using namespace ci;
using namespace ci::app;

#include "LensFlareElement.hpp"

class LensFlareApertureReflection: public LensFlareElement
{
    
public:
    
    LensFlareApertureReflection( std::string filename );
    
    void draw( vec2, bool, float ) override;
    
private:
    
    float calculateScale( float );
    
    gl::Texture2dRef texture;
};

#endif /* LensFlareApertureReflection_hpp */
