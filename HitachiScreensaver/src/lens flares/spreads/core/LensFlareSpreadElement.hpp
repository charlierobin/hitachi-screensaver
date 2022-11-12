#ifndef LensFlareSpreadElement_hpp
#define LensFlareSpreadElement_hpp

#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;

class LensFlareSpreadElement
{
    
public:
    
    LensFlareSpreadElement( std::string );
    
    void draw( vec2, vec2, bool, float, float );
    
private:
    
    vec2 getPositionOnAxis( float, vec2, vec2 );

    float positionOnAxis = 1;
    
    float scale = 1;
    
    float alpha = 0.2;
    
    cinder::gl::Texture2dRef texture;
};

#endif /* LensFlareSpreadElement_hpp */
