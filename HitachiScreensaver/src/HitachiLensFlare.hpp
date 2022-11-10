#ifndef HitachiLensFlare_hpp
#define HitachiLensFlare_hpp

#include "LensFlareCentre.hpp"
#include "LensFlareCentralGlow.hpp"
#include "LensFlareApertureReflection.hpp"
#include "LensFlareChromaHoop.hpp"
#include "LensFlareChromaFans.hpp"

#include "LensFlare.hpp"

using namespace ci;
using namespace ci::app;

class HitachiLensFlare: public LensFlare
{

public:
    
    HitachiLensFlare()
    {
        add( new LensFlareCentre( "centre.jpg" ) );
//        add( new LensFlareCentralGlow() );
        add( new LensFlareApertureReflection( "aperture-flare.jpg" ) );
//        add( new LensFlareChromaHoop() );
        add( new LensFlareChromaFans() );
    };
};

#endif /* HitachiLensFlare_hpp */
