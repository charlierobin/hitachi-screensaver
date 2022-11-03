#include "Placard.hpp"

Placard::Placard()
{
    initialise();
    angle_ = HALF_A_TURN;
}

void Placard::initialise()
{
    setSpeed( 6.0 );
    ObjLoader loader( loadResource( "billboard.obj" ) );
    placard_ = gl::Batch::create( loader, gl::context()->getStockShader( gl::ShaderDef().color().texture() ) );
    loadTexture( "uvGrid_512.png" );
}

void Placard::loadTexture( string name )
{
    auto img = loadImage( loadResource( name ) );
    texture_ = gl::Texture::create( img );
}

void Placard::setSpeed( float secondsPerOrbit )
{
    //    speed_ = ONE_TURN / ( APPROX_FRAMERATE * secondsPerOrbit );
}

void Placard::randomise()
{
    setSpeed( randFloat( 8.0f, 20.0f ) );
    zRotation_ = randFloat( - HALF_A_TURN, HALF_A_TURN );
    yRotation_ = randFloat( - HALF_A_TURN, HALF_A_TURN );
    angle_ = randFloat( 0.0f, ONE_TURN );
    
    speedPerSecond_ = speedPerSecond_ * randFloat( 0.9f, 1.1f );
}

void Placard::update( float time, std::vector<IItem *> items, int index )
{
    angle_ = angle_ + ( speedPerSecond_ * time );
    if ( angle_ >= ONE_TURN ) angle_ = 0.0;
}

void Placard::draw( bool mask )
{
    if ( mask ) return;
    
//    gl::disableDepthRead();
//    gl::disableDepthWrite();
    
    gl::ScopedTextureBind tex0( texture_ );
    
    cinder::gl::color( 1,1,1 );
    
    gl::pushModelMatrix();
    
    gl::rotate( zRotation_, vec3( 0, 0, 1 ) );
    gl::rotate( yRotation_, vec3( 0, 1, 0 ) );
    gl::rotate( -angle_, vec3( 1, 0, 0 ) );
    
    placard_->draw();
    
    gl::popModelMatrix();
    
//    gl::enableDepthRead();
//    gl::enableDepthWrite();
}

