#include "LensFlareChromaFans.hpp"

using namespace ci;
using namespace ci::app;

LensFlareChromaFans::LensFlareChromaFans()
{
    Surface img = loadImage( loadResource( "fan.jpg" ) );
    
    texture = gl::Texture::create( img );
}

void LensFlareChromaFans::draw( vec2 position, vec2 axis, bool onScreen, float intensity, float angle )
{
    if ( ! onScreen ) return;
    
    float scaled = texture->getWidth() * scale * intensity;
    
    float radius = intensity * 200;
    
    {
        gl::ScopedModelMatrix scope;
        
        gl::translate( position );
        
        gl::rotate( angle );
        
        gl::translate( 0, radius );
        
        
        gl::draw( texture, Rectf( - scaled / 2, - scaled / 2, scaled / 2, scaled / 2 ) );
    }
    
    {
        gl::ScopedModelMatrix scope;
        
        gl::translate( position );
        
        gl::rotate( angle );
        
        gl::translate( 0, - radius );
        
        
        gl::rotate( HALF_A_TURN );
        
        
        gl::draw( texture, Rectf( - scaled / 2, - scaled / 2, scaled / 2, scaled / 2 ) );
    }
}


