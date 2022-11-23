#include "LensFlareCentre.hpp"

using namespace ci;
using namespace ci::app;

LensFlareCentre::LensFlareCentre( std::string filename )
{
    Surface img = loadImage( loadResource( filename ) );
    
    texture = gl::Texture::create( img );
}

void LensFlareCentre::draw( vec2 position, vec2 axis, bool onScreen, float intensity, float angle )
{
    if ( ! onScreen ) return;
    
    float scaled = texture->getWidth() * intensity * 0.5;
    
    gl::translate( position );
    
    gl::rotate( angle );
    
    gl::draw( texture, Rectf( - scaled / 2, - scaled / 2, scaled / 2, scaled / 2 ) );
}
