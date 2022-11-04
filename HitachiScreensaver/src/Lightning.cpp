#include "Lightning.hpp"

Lightning::Lightning()
{
    auto img = loadImage( loadResource( "lightning.jpg" ) );
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
    
    gl::enableAdditiveBlending();
    
    gl::drawBillboard( vec3( 0, 0, 0 ), vec2( 3, 6.5 ), 0 , vec3( 1, 0, 0 ), vec3( 0, -1, 0 ) );

    gl::enableAlphaBlending();
}
