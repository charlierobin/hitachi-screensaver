#ifndef LensFlare_hpp
#define LensFlare_hpp

#include "LensFlareElement.hpp"

using namespace ci;
using namespace ci::app;

class LensFlare
{

public:
    
    void add( LensFlareElement * );
    void draw();
    
    vec2 position;
    float intensity = 1.0;
    
private:
    
    std::vector<LensFlareElement *> elements;
    
};

#endif /* LensFlare_hpp */
