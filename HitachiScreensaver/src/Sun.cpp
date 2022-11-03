#include "Sun.hpp"

void Sun::update( float time, CameraPersp camera )
{
    sunAngle_ = sunAngle_ + ( time * speed );
    
    float zTurn = ONE_TURN / 20;
    
    sunPosition_ = vec3( 0.0f, 0.0f, SUN_ORBIT_RADIUS );
    
    sunPosition_ = glm::rotate( sunPosition_, sunAngle_, AROUND_Y_AXIS );
    sunPosition_ = glm::rotate( sunPosition_, zTurn, AROUND_Z_AXIS );
    
    sunPositionOnScreen_ = camera.worldToScreen( sunPosition_, getWindowWidth(), getWindowHeight() );
}

void Sun::draw()
{
//    gl::context()->getStockShader( gl::ShaderDef().color() )->bind();
//
//    gl::color( 1.0, 1.0, 0.0 );
//
//    gl::pushModelMatrix();
//
//    gl::drawSphere( sunPosition_, SUN_RADIUS );
//
//    gl::popModelMatrix();
}

bool Sun::isOnScreen()
{
    if ( sunPositionOnScreen_.x > 0 && sunPositionOnScreen_.x < getWindowWidth() && sunPositionOnScreen_.y > 0 && sunPositionOnScreen_.y < getWindowHeight() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

