#include "LensFlare.hpp"

LensFlare::LensFlare()
{
    Surface img = loadImage( loadResource( "centre.jpg" ) );
    
    this->texture = gl::Texture::create( img );
    
    this->position = vec2( 10, 10 );
}

void LensFlare::update( float time, std::vector<IItem *> items, int index )
{
}

void LensFlare::draw( bool mask )
{
    if ( mask ) return;
    
    float scaledWidth = 1024 * intensity * 0.5;
    float scaledHeight = 1024 * intensity * 0.5;
    
    gl::setMatricesWindow( getWindowSize() );
    
    gl::disableAlphaBlending();
    
    gl::enableAdditiveBlending();
    
    cinder::gl::color( 1.0, 1.0, 1.0, 1.0 );
    
    gl::pushModelView();
    
    gl::translate( this->position );
    
    gl::translate( - scaledWidth / 2, - scaledHeight / 2 );
    
    gl::draw( texture, Rectf( 0, 0, scaledWidth, scaledHeight ) );
    
    gl::enableAlphaBlending();
    
    gl::popModelView();
}