#ifndef LensFlareChromaFans_hpp
#define LensFlareChromaFans_hpp

#include "macros.h"

#include "LensFlareElement.hpp"

class LensFlareChromaFans: public LensFlareElement
{
    
public:
    
    LensFlareChromaFans();
    
    void draw( vec2, vec2, bool, float, float ) override;
    
private:
    
    float angle = ONE_DEGREE * 90;
    
    float scale = 0.5;
    
    gl::Texture2dRef texture;
};

#endif /* LensFlareChromaFans_hpp */
