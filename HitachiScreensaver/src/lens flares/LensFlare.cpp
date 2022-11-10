#include "LensFlare.hpp"

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
        
        element->draw( this->position, this->onScreen, this->intensity );
    }
    
    gl::enableAlphaBlending();
}

