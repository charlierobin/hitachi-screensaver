#include "LensFlareSpreadElement.hpp"

using namespace ci;
using namespace ci::app;

LensFlareSpreadElement::LensFlareSpreadElement( std::string resourceName )
{
    this->positionOnAxis = randFloat( 0.1, 2 );
    
    this->scale = randFloat( 0.1, 0.3 );
    
    this->alpha = randFloat( 0.1, 0.3 );
    
    Surface img = loadImage( loadResource( resourceName ) );
    
    this->texture = gl::Texture::create( img );
}

void LensFlareSpreadElement::draw( vec2 position, vec2 axis, bool onScreen, float intensity, float angle )
{
    float scaled = texture->getWidth() * this->scale * intensity;

    vec2 p = this->getPositionOnAxis( positionOnAxis, position, axis );

    gl::ScopedModelMatrix scope;

    gl::color( 1, 1, 1, this->alpha );
    
    gl::translate( p );

    gl::rotate( angle );

    gl::draw( texture, Rectf( - scaled / 2, - scaled / 2, scaled / 2, scaled / 2 ) );
}

vec2 LensFlareSpreadElement::getPositionOnAxis( float distanceOnAxis, vec2 position, vec2 axis )
{
    float x = 0;
    float y = 0;
    
    float xOpposite = 0;
    float yOpposite = 0;
    
    float angle = 0;
    
    if ( position.x < axis.x && position.y < axis.y )
    {
        // top left
        
        x = axis.x - position.x;
        y = axis.y - position.y;
        
        xOpposite = axis.x + x;
        yOpposite = axis.y + y;
    }
    else if ( position.x < axis.x && position.y > axis.y )
    {
        // bottom left
        
        x = axis.x - position.x;
        y = position.y - axis.y;
        
        xOpposite = axis.x + x;
        yOpposite = axis.y - y;
    }
    else if ( position.x > axis.x && position.y < axis.y )
    {
        // top right
        
        x = position.x - axis.x;
        y = axis.y - position.y;
        
        xOpposite = axis.x - x;
        yOpposite = axis.y + y;
    }
    else
    {
        // bottom right
        
        x = position.x - axis.x;
        y = position.y - axis.y;
        
        xOpposite = axis.x - x;
        yOpposite = axis.y - y;
    }
    
    angle = atan2( y, x );
    
    float lengthOfAxis = 2 * hypot( x, y );
    
    float otherAngle = ( 3.14 / 2.0 ) - angle;
    
    float elementDistanceOnAxis = lengthOfAxis * distanceOnAxis;
    
    if ( position.x < axis.x && position.y < axis.y )
    {
        return vec2( position.x + sin( otherAngle ) * elementDistanceOnAxis, position.y + cos( otherAngle ) * elementDistanceOnAxis );
    }
    else if ( position.x < axis.x && position.y > axis.y )
    {
        return vec2( position.x + sin( otherAngle ) * elementDistanceOnAxis, position.y - cos( otherAngle ) * elementDistanceOnAxis);
    }
    else if ( position.x > axis.x && position.y < axis.y )
    {
        return vec2( position.x - sin( otherAngle ) * elementDistanceOnAxis, position.y + cos( otherAngle ) * elementDistanceOnAxis );
    }
    else
    {
        return vec2( position.x - sin( otherAngle ) * elementDistanceOnAxis, position.y - cos( otherAngle ) * elementDistanceOnAxis );
    }
}

