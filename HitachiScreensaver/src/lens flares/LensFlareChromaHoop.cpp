#include "LensFlareChromaHoop.hpp"

using namespace ci;
using namespace ci::app;

LensFlareChromaHoop::LensFlareChromaHoop()
{
    Surface img = loadImage( loadResource( "chroma-hoop.jpg" ) );
    
    texture = gl::Texture::create( img );
}

void LensFlareChromaHoop::draw( vec2 position, bool onScreen, float intensity )
{
    if ( ! onScreen ) return;
    
    
    
    
    float scaledWidth = ( hypot( 320 - position.x, 240 - position.y ) ) * 2;
    
    scaledWidth = scaledWidth - ( scaledWidth / 1024 );
    
    float scaledHeight = scaledWidth;
    
    float alpha = this->scaleBetween( scaledWidth, 400, 200 );
    
    alpha = alpha / 2;
    
    if ( scaledWidth > getWindowWidth() + 500 ) return;
    
    gl::ScopedColor colour( 1, 1, 1, alpha );
    
    gl::ScopedModelMatrix scope;
    
    gl::translate( 320, 240 );
    
    //    gl::rotate( this->getAngleFromCentre() );
    
    gl::rotate( atan2( 240 - position.y, 320 - position.x ) );
    
    gl::draw( texture, Rectf( - scaledWidth / 2, - scaledHeight / 2, scaledWidth / 2, scaledHeight / 2 ) );
    
    
    //    float scaledWidth = texture->getWidth() * intensity * 0.5;
    //    float scaledHeight = texture->getHeight() * intensity * 0.5;
    //
    //    gl::translate( position );
    //    gl::translate( - scaledWidth / 2, - scaledHeight / 2 );
    //
    //    gl::draw( texture, Rectf( 0, 0, scaledWidth, scaledHeight ) );
}


float LensFlareChromaHoop::scaleBetween( float value, float upper, float lower )
{
    if ( value <= upper && value >= lower )
    {
        return ( value - lower ) / ( upper - lower );
    }
    else if ( value < lower )
    {
        return 0.0;
    }
    return 1.0;
}

//float LensFlareChromaHoop::getAngleFromCentre()
//{
//    float xCentre = 320;
//    float yCentre = 240;
//
//    return atan2( 240 - position.y, 320 - position.x );
//}
//
//
