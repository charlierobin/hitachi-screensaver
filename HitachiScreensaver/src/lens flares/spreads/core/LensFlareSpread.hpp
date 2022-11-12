#ifndef LensFlareSpread_hpp
#define LensFlareSpread_hpp

#include "LensFlareElement.hpp"

#include "LensFlareSpreadElement.hpp"

class LensFlareSpread: public LensFlareElement
{
    
public:
    
    LensFlareSpread( int, std::string );
    
    void draw( vec2, vec2, bool, float, float ) override;
    
    std::vector<LensFlareSpreadElement *> elements_;
    
    cinder::Color colour_;
    
    bool useColour_ = false;
    
    float colourVariationRange_ = 0;
};

#endif /* LensFlareSpread_hpp */
