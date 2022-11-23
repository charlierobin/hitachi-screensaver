#include "HeroPyramidSlice.hpp"

HeroPyramidSlice::HeroPyramidSlice( string group, float offset )
{
    ObjLoader loader( loadResource( "pyramid.obj" ) );
    batchRef_ = gl::Batch::create( loader.groupName( group ), gl::context()->getStockShader( gl::ShaderDef().texture().lambert() ) );
    
    offset_ = offset;
    
    y_ = -400.0f;
    x_ = 0.0f;
    z_ = 0.0f;
}

void HeroPyramidSlice::trigger( float duration )
{
    duration_ = duration;
    busy_ = true;
    CueRef cue = timeline().add( bind( &HeroPyramidSlice::startComingIn, this ), timeline().getCurrentTime() + offset_ );
}

void HeroPyramidSlice::update( float time )
{
    if ( state_ == COMING_IN )
    {
        ++counter_;
        y_ = Tweening::easeOutCubic( counter_, -400.0f, 400.0f, COMING_IN_COUNTER_MAX );
        angle_ = Tweening::easeOutCubic( counter_, 0.0f, HALF_A_TURN, COMING_IN_COUNTER_MAX );
        
        if ( counter_ > COMING_IN_COUNTER_MAX ) state_ = ON_SCREEN;
    }
    if ( state_ == ON_SCREEN )
    {
        CueRef cue = timeline().add( bind( &HeroPyramidSlice::startGoingOut, this ), timeline().getCurrentTime() + duration_ + offset_ );
    }
    else if ( state_ == GOING_OUT )
    {
        ++counter_;
        y_ = Tweening::easeInCubic( counter_, 0.0f, 400.0f, GOING_OUT_COUNTER_MAX );
        angle_ = Tweening::easeInCubic( counter_, HALF_A_TURN, HALF_A_TURN, GOING_OUT_COUNTER_MAX );
        
        if ( counter_ > GOING_OUT_COUNTER_MAX )
        {
            state_ = OFF_SCREEN;
            busy_ = false;
        }
    }
    else
    {
        // nothing
    }
}

void HeroPyramidSlice::startComingIn()
{
    state_ = COMING_IN;
    counter_ = 0;
}

void HeroPyramidSlice::startGoingOut()
{
    state_ = GOING_OUT;
    counter_ = 0;
}

void HeroPyramidSlice::draw()
{
    gl::pushModelMatrix();
    
    gl::rotate( angle_, AROUND_Y_AXIS );
    gl::translate( x_, y_, z_ );
    
    batchRef_->draw();
    
    gl::popModelMatrix();
}

bool HeroPyramidSlice::isBusy() {
    return busy_;
}

