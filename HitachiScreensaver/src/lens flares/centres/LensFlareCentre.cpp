#include "LensFlareCentre.hpp"

using namespace ci;
using namespace ci::app;

LensFlareCentre::LensFlareCentre( std::string filename )
{
    Surface img = loadImage( loadResource( filename ) );
    
    texture = gl::Texture::create( img );
}

void LensFlareCentre::draw( vec2 position, bool onScreen, float intensity )
{
    if ( ! onScreen ) return;
    
    float scaledWidth = texture->getWidth() * intensity * 0.5;
    float scaledHeight = texture->getHeight() * intensity * 0.5;
    
    gl::translate( position );
    gl::translate( - scaledWidth / 2, - scaledHeight / 2 );
    
    gl::draw( texture, Rectf( 0, 0, scaledWidth, scaledHeight ) );
}
