#include "LensFlare.hpp"

LensFlare::LensFlare()
{
    this->axis = vec2( getWindowWidth() / 2, getWindowHeight() / 2 );
}

void LensFlare::add( LensFlareElement * element)
{
    this->elements.push_back( element );
}

void LensFlare::draw()
{
    gl::setMatricesWindow( getWindowSize() );
    
    gl::disableDepthRead();
    gl::disableDepthWrite();
    
    gl::disableAlphaBlending();
    
    gl::enableAdditiveBlending();
    
    cinder::gl::color( 1, 1, 1, 1 );
    
    for ( LensFlareElement * element : this->elements )
    {
        gl::ScopedModelMatrix scope;
        
        element->draw( this->position, this->axis, this->onScreen, this->intensity, this->angle );
    }
    
    gl::enableAlphaBlending();
}

