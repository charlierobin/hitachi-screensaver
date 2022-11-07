#include "Placard.hpp"

Placard::Placard()
{
    ObjLoader loader( loadResource( "billboard.obj" ) );
    placard_ = gl::Batch::create( loader, gl::context()->getStockShader( gl::ShaderDef().color().texture() ) );
    
    auto img = loadImage( loadResource( "uvGrid_512.png" ) );
    texture_ = gl::Texture::create( img );
    
    angle_ = HALF_A_TURN;
}

Placard::Placard( string name ) : Placard()
{
    auto img = loadImage( loadResource( name ) );
    texture_ = gl::Texture::create( img );
    
    zRotation_ = randFloat( - HALF_A_TURN, HALF_A_TURN );
    yRotation_ = randFloat( - HALF_A_TURN, HALF_A_TURN );
    angle_ = randFloat( 0.0f, ONE_TURN );
    
    speedPerSecond_ = speedPerSecond_ * randFloat( 1.0f, 1.5f );
}

void Placard::update( float time )
{
    angle_ = angle_ + ( speedPerSecond_ * time );
}

void Placard::draw()
{
    gl::disableDepthRead();
    gl::disableDepthWrite();
    
//    gl::disableAlphaBlending();
//    gl::enableAdditiveBlending();
    
    gl::ScopedTextureBind tex0( texture_ );
    
    cinder::gl::color( colour_ );
    
    gl::pushModelMatrix();
    
    gl::rotate( zRotation_, vec3( 0, 0, 1 ) );
    gl::rotate( yRotation_, vec3( 0, 1, 0 ) );
    gl::rotate( -angle_, vec3( 1, 0, 0 ) );
    
    placard_->draw();
    
    gl::popModelMatrix();
    
//    gl::enableAlphaBlending();
    
    gl::enableDepthRead();
    gl::enableDepthWrite();
}

