#include "LensFlareSpread.hpp"

#include "LensFlareSpreadElement.hpp"

using namespace ci;
using namespace ci::app;

LensFlareSpread::LensFlareSpread( int numberOfElements, std::string resourceName )
{
    for ( int i = 0; i < numberOfElements; ++i )
    {
        elements_.push_back( new LensFlareSpreadElement( resourceName ) );
    }
}

void LensFlareSpread::draw( vec2 position, vec2 axis, bool onScreen, float intensity, float angle )
{
    for ( LensFlareSpreadElement * element : elements_ )
    {
        element->draw( position, axis, onScreen, intensity, angle );
    }
}

