#include "LensFlareApertureReflection.hpp"

using namespace ci;
using namespace ci::app;

LensFlareApertureReflection::LensFlareApertureReflection( std::string filename )
{
    Surface img = loadImage( loadResource( filename ) );
    texture = gl::Texture::create( img );
}

void LensFlareApertureReflection::draw( vec2 position, vec2 axis, bool onScreen, float intensity, float angle )
{
    if ( ! onScreen ) return;
    
    float scaled = texture->getWidth() * 1.2;

    Rectf s = Rectf( 0, 0, getWindowWidth(), getWindowHeight() );
    
    if ( s.contains( position ) ) return;
    
    s = Rectf( -100, -100, getWindowWidth() + 100,getWindowHeight() + 100 );
    
    if ( ! s.contains( position ) ) return;
    
    if ( position.x < 0 && position.x >= -100 )
    {
        gl::translate( 0, position.y );
        
        scaled = scaled * calculateScale( position.x );
    }
    else if ( position.x > getWindowWidth() && position.x <= getWindowWidth() + 100 )
    {
        gl::translate( getWindowWidth(), position.y );
        gl::rotate( HALF_A_TURN );
        
        scaled = scaled * calculateScale( position.x - getWindowWidth() );
    }
    else if ( position.y < 0 && position.y >= -100 )
    {
        gl::translate( position.x, 0 );
        gl::rotate( QUARTER_OF_A_TURN );
        
        scaled = scaled * calculateScale( position.y );
    }
    else if ( position.y > getWindowHeight() && position.y <= getWindowHeight() + 100 )
    {
        gl::translate( position.x, getWindowHeight() );
        gl::rotate( THREE_QUARTERS_OF_A_TURN );
        
        scaled = scaled * calculateScale( position.y - getWindowHeight() );
    }
    
    gl::draw( texture, Rectf( 0, - scaled / 2, scaled, scaled / 2 ) );
}

float LensFlareApertureReflection::calculateScale( float value )
{
    value = std::abs( value );
    
    if ( value < 50 )
    {
        // scales down from 50 to 0
        return value / 50.0;
    }
    // scales down from 50 to 100
    return (  100.0 - value ) / 50.0;
}

