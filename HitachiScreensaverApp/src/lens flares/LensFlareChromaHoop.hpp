#ifndef LensFlareChromaHoop_hpp
#define LensFlareChromaHoop_hpp

using namespace ci;
using namespace ci::app;

#include "LensFlareElement.hpp"

class LensFlareChromaHoop: public LensFlareElement
{
    
public:
    
    LensFlareChromaHoop();
    
    void draw( vec2, vec2, bool, float, float ) override;
    
private:
    
    float scaleBetween( float, float, float );
    float getAngleFromCentre();
    
    float calculateScale( float );
    
    float scale = 1;
    
    gl::Texture2dRef texture;
};

#endif /* LensFlareChromaHoop_hpp */
