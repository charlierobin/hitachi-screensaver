#ifndef LensFlareCentre_hpp
#define LensFlareCentre_hpp

using namespace ci;
using namespace ci::app;

#include "LensFlareElement.hpp"

class LensFlareCentre: public LensFlareElement
{
    
public:
    
    LensFlareCentre( std::string filename );
    
    void draw( vec2, vec2, bool, float, float ) override;
    
private:
    
    gl::Texture2dRef texture;
    
};

#endif /* LensFlareCentre_hpp */
