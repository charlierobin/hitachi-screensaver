#include "Starfield.hpp"

Starfield::Starfield()
{
    auto img = loadImage( loadResource( "stars_top3.png" ) );
    topTexture = gl::Texture::create( img );
    
    img = loadImage( loadResource( "stars_bottom4.png" ) );
    bottomTexture = gl::Texture::create( img );
    
    img = loadImage( loadResource( "stars_left2.png" ) );
    leftTexture = gl::Texture::create( img );
    
    img = loadImage( loadResource( "stars_right1.png" ) );
    rightTexture = gl::Texture::create( img );
    
    img = loadImage( loadResource( "stars_front5.png" ) );
    frontTexture = gl::Texture::create( img );
    
    img = loadImage( loadResource( "stars_back6.png" ) );
    backTexture = gl::Texture::create( img );
    
    ObjLoader loader( loadResource( "starfield.obj" ) );
    
    topSection = gl::Batch::create( loader.groupName( "topSection" ), gl::context()->getStockShader( gl::ShaderDef().color().texture() ) );
    bottomSection = gl::Batch::create( loader.groupName( "bottomSection" ), gl::context()->getStockShader( gl::ShaderDef().color().texture() ) );
    leftSection = gl::Batch::create( loader.groupName( "leftSection" ), gl::context()->getStockShader( gl::ShaderDef().color().texture() ) );
    rightSection = gl::Batch::create( loader.groupName( "rightSection" ), gl::context()->getStockShader( gl::ShaderDef().color().texture() ) );
    frontSection = gl::Batch::create( loader.groupName( "frontSection" ), gl::context()->getStockShader( gl::ShaderDef().color().texture() ) );
    backSection = gl::Batch::create( loader.groupName( "backSection" ), gl::context()->getStockShader( gl::ShaderDef().color().texture() ) );
    
    rotationAxis = vec3( randFloat( -1.0f, 1.0f ), randFloat( -1.0f, 1.0f ), randFloat( -1.0f, 1.0f ) );
}

void Starfield::update( float time, std::vector<IItem *> items, int index )
{
    angle = angle + ( rotationSpeedPerSecond * time );
    
//    if ( angle >= ONE_TURN ) angle = 0.0;
}

void Starfield::draw( bool mask )
{
    if ( mask ) return;
        
    gl::color( 1.0, 1.0, 1.0, 1.0 );
    
    gl::pushModelMatrix();
    
    gl::translate( CAMERA_POSITION );
    
    gl::scale( 5.0f, 5.0f, 5.0f );
    
    gl::rotate( angle, rotationAxis );
    
    gl::ScopedTextureBind tex0( topTexture );
    topSection->draw();
    
    gl::ScopedTextureBind tex1( bottomTexture );
    bottomSection->draw();
    
    gl::ScopedTextureBind tex2( leftTexture );
    leftSection->draw();
    
    gl::ScopedTextureBind tex3( rightTexture );
    rightSection->draw();
    
    gl::ScopedTextureBind tex4( frontTexture );
    frontSection->draw();
    
    gl::ScopedTextureBind tex5( backTexture );
    backSection->draw();
    
    gl::popModelMatrix();
}



