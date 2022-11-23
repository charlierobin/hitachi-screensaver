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
    
    
    img = loadImage( loadResource( "twinkle.png" ) );
    twinkleTexture = gl::Texture::create( img );
    
    
    for ( int i = 0; i < MAX_TWINKLE_FRAMES; ++i )
    {
        float u = ( ( int ) i / 8 ) * 0.125;
        float v = ( ( int ) i % 8 ) * 0.125;

        auto mesh = geom::Rect( Rectf( -STAR_SIZE, -STAR_SIZE, STAR_SIZE, STAR_SIZE ) ).texCoords( vec2( u, v ), vec2( u + 0.125, v ), vec2( u + 0.125, v + 0.125 ), vec2( u, v + 0.125 ) );
    
        this->starBatches.push_back( gl::Batch::create( mesh, gl::context()->getStockShader( gl::ShaderDef().color().texture() ) ) );
    }
    
    for ( int i = 0; i < NUMBER_OF_STARS; ++i )
    {
        this->stars.push_back( {
            randInt( MAX_TWINKLE_FRAMES ),
            randInt( 0, 2 ) > 0 ? +1 : -1,
            randFloat( ONE_TURN ),
            randFloat( ONE_TURN ),
            randFloat( -ONE_TURN, ONE_TURN ),
            randFloat( -0.01, 0.01 ),
            randInt( 0, 2 ) > 0 ? Color( 0.8, 0.2, 0.2 ) : Color( 0.2, 0.2, 0.8 )
        } );
    }
}

void Starfield::update( float time )
{
    angle = angle + ( rotationSpeedPerSecond * time );
    
    for ( int i = 0; i < NUMBER_OF_STARS; ++i )
    {
        this->stars[ i ].step = this->stars[ i ].step + this->stars[ i ].direction;
        
        if ( this->stars[ i ].step >= MAX_TWINKLE_FRAMES )
        {
            this->stars[ i ].step = MAX_TWINKLE_FRAMES - 1;
            this->stars[ i ].direction = -1;
        }
        else if ( this->stars[ i ].step < 0 )
        {
            this->stars[ i ].step = 0;
            this->stars[ i ].direction = +1;
        }
        
        this->stars[ i ].rotationZ = this->stars[ i ].rotationZ + this->stars[ i ].rotationZDelta;
    }
}

void Starfield::draw()
{
    gl::disableDepthRead();
    gl::disableDepthWrite();
    
    gl::color( 1, 1, 1 );
    
    gl::pushModelMatrix();
    
    gl::translate( CAMERA_POSITION );
    
    gl::scale( 5.0f, 5.0f, 5.0f );
    
    gl::rotate( angle, rotationAxis );
    
    topTexture->bind();
    topSection->draw();
    
    bottomTexture->bind();
    bottomSection->draw();
    
    leftTexture->bind();
    leftSection->draw();
    
    rightTexture->bind();
    rightSection->draw();
    
    frontTexture->bind();
    frontSection->draw();
    
    backTexture->bind();
    backSection->draw();
    
    this->twinkleTexture->bind();
    
    gl::enableAdditiveBlending();
    
    for ( int i = 0; i < NUMBER_OF_STARS; ++i )
    {
        gl::pushModelMatrix();
        
        gl::color( 1, 1, 1 );
        
        gl::rotate( this->stars[ i ].rotationX, vec3( 1, 0, 0 ) );
        gl::rotate( this->stars[ i ].rotationY, vec3( 0, 1, 0 ) );
        gl::rotate( this->stars[ i ].rotationZ, vec3( 0, 0, 1 ) );
        
        gl::translate( 0, 0, -STARS_Z + ( i * 1 ) );
        
        gl::color( this->stars[ i ].colour );
        
        starBatches[ stars[ i ].step ]->draw();
        
        gl::popModelMatrix();
    }
    
    gl::enableAlphaBlending();
    
    gl::enableDepthRead();
    gl::enableDepthWrite();
    
    gl::popModelMatrix();
}



