#include "HeroPyramid.hpp"

HeroPyramid::HeroPyramid()
{
    slices_.push_back( new HeroPyramidSlice( "Obj1", 0.2f ) );
    slices_.push_back( new HeroPyramidSlice( "Obj2", 0.4f ) );
    slices_.push_back( new HeroPyramidSlice( "Obj3", 0.6f ) );
    slices_.push_back( new HeroPyramidSlice( "Obj4", 0.8f ) );
    slices_.push_back( new HeroPyramidSlice( "Obj5", 1.0f ) );
    slices_.push_back( new HeroPyramidSlice( "Obj6", 1.2f ) );
    
    auto img = loadImage( loadResource( "text-bits.png" ) );
    mTexture = gl::Texture::create( img );
    
    x_ = 0.0f;
    y_ = -3.0f;
    z_ = -40.0f;
}

void HeroPyramid::update( float time )
{
    angle_ = angle_ + 0.01f;
    
    if ( angle_ > ONE_TURN ) angle_ = 0.0;
    
    bool busy = false;
    
    for ( int i = 0; i < slices_.size(); ++i )
    {
        slices_[ i ]->update( time );
        if ( slices_[ i ]->isBusy() ) busy = true;
    }
    
    if ( ! busy && ! cued_ )
    {
        CueRef cue = timeline().add( bind( &HeroPyramid::startComingIn, this ), timeline().getCurrentTime() + randFloat( 15.0f, 25.0f ) );
        cued_ = true;
    }
}

void HeroPyramid::draw()
{
    gl::pushModelMatrix();
    
    gl::translate( x_, y_, z_ );
    gl::scale( 0.1, 0.1, 0.1 );
    
    gl::rotate( randomZRotation_, AROUND_Z_AXIS );
    gl::rotate( angle_, AROUND_Y_AXIS );
    
    cinder::gl::color( 1.0, 1.0, 1.0, 1.0 );
    cinder::gl::ScopedTextureBind tex1( mTexture );
    
    for ( int i = 0; i < slices_.size(); ++i )
    {
        slices_[ i ]->draw();
    }
    
    gl::popModelMatrix();
}

void HeroPyramid::startComingIn()
{
    float duration = randFloat( 5.0f, 10.0f );
    
    for ( int i = 0; i < slices_.size(); ++i )
    {
        slices_[ i ]->trigger( duration );
    }
    randomZRotation_ = randFloat( -0.05f * ONE_TURN, 0.05f * ONE_TURN );
    cued_ = false;
}

