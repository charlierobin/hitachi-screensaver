#ifndef LensFlare_hpp
#define LensFlare_hpp

#include "LensFlareElement.hpp"

using namespace ci;
using namespace ci::app;

class LensFlare
{

public:
    
    LensFlare();
    
    void add( LensFlareElement * );
    void draw();
    
    bool onScreen;
    vec2 position;
    vec2 axis;
    float intensity = 1.0;
    float angle;
    
private:
    
    std::vector<LensFlareElement *> elements;
    
};

#endif /* LensFlare_hpp */
