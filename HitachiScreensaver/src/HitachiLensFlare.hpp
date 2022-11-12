#ifndef HitachiLensFlare_hpp
#define HitachiLensFlare_hpp

#include "macros.h"

#include "LensFlareCentre.hpp"
#include "LensFlareCentralGlow.hpp"
#include "LensFlareApertureReflection.hpp"
#include "LensFlareChromaHoop.hpp"
#include "LensFlareChromaFans.hpp"
#include "LensFlareSpreadPentagons.hpp"
#include "LensFlareCentralRing.hpp"

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
        add( new LensFlareChromaHoop() );
//        add( new LensFlareChromaFans() );
        add( new LensFlareSpreadPentagons( 5 ) );
//        add( new LensFlareCentralRing() );
    };
    
    void update()
    {
        this->angle = this->angle + ( ONE_DEGREE / 5 );
    };
};

#endif /* HitachiLensFlare_hpp */
