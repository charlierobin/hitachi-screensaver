#include "Lightning.hpp"

Lightning::Lightning()
{
    auto img = loadImage( loadResource( "lightning.png" ) );
    this->texture = gl::Texture::create( img );
}

void Lightning::update()
{
}

void Lightning::draw()
{
    auto shader = gl::getStockShader( gl::ShaderDef().color().texture() );
    shader->bind();
    
    gl::ScopedTextureBind tex0( this->texture );
    
    gl::color( 1, 1, 1 );
    
    gl::disableDepthRead();
    gl::disableDepthWrite();
    
//    gl::disableAlphaBlending();
//    gl::enableAdditiveBlending();
    
    gl::drawBillboard( vec3( -50, 0, -LIGHTNING_Z ), vec2( 60, 110 ), ONE_DEGREE * 10 , vec3( 1, 0, 0 ), vec3( 0, -1, 0 ) );

    gl::drawBillboard( vec3( 50, 0, -LIGHTNING_Z ), vec2( 70, 120 ), ONE_DEGREE * -5 , vec3( 1, 0, 0 ), vec3( 0, -1, 0 ) );
    
//    gl::enableAlphaBlending();
    
    gl::enableDepth();
}

