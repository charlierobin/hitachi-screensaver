#include "Sun.hpp"

void Sun::update( float time, CameraPersp camera )
{
    angle = angle + ( time * speed );
    
    float zTurn = ONE_TURN / 20;
    
    position = vec3( 0.0f, 0.0f, SUN_ORBIT_RADIUS );
    
    position = glm::rotate( position, angle, AROUND_Y_AXIS );
    position = glm::rotate( position, zTurn, AROUND_Z_AXIS );
    
    onScreen = position.z < 0 ? true : false;
    
    positionOnScreen = camera.worldToScreen( position, getWindowWidth(), getWindowHeight() );
}

void Sun::draw()
{
    gl::context()->getStockShader( gl::ShaderDef().color() )->bind();

    gl::color( 1, 1, 0 );

    gl::pushModelMatrix();

    gl::drawSphere( position, SUN_RADIUS );

    gl::popModelMatrix();
}

