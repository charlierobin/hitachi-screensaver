#include "Pyramid.hpp"

Pyramid::Pyramid()
{
    ObjLoader loader( loadResource( "pyramid.obj" ) );
    
    this->slices.push_back( gl::Batch::create( loader.groupName( "Obj1" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    this->slices.push_back( gl::Batch::create( loader.groupName( "Obj2" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    this->slices.push_back( gl::Batch::create( loader.groupName( "Obj3" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    this->slices.push_back( gl::Batch::create( loader.groupName( "Obj4" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    this->slices.push_back( gl::Batch::create( loader.groupName( "Obj5" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    this->slices.push_back( gl::Batch::create( loader.groupName( "Obj6" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
}

//Pyramid::Pyramid( vec3 position, vec3 speed ) : Pyramid()
//{
//    this->mPosition = position;
//    this->speedPerSecond = speed;
//    this->tumbleAxis_ = vec3( randFloat( -1, 1 ), randFloat( -1, 1 ), randFloat( -1, 1 ) );
//}

Pyramid::Pyramid( vec3 topLeftNear, vec3 bottomRightNear, vec3 topLeftFar, vec3 bottomRightFar ) : Pyramid()
{
    this->topLeftNear = topLeftNear;
    this->bottomRightNear = bottomRightNear;
    this->topLeftFar = topLeftFar;
    this->bottomRightFar = bottomRightFar;
    
    this->cue = timeline().add( std::bind( &Pyramid::start, this ), timeline().getCurrentTime() + randFloat( 5, 15 ) );
}

void Pyramid::start()
{
    this->active = true;
    this->activated = false;
    
    switch ( randInt( 4 ) ) {
            
        case 0:
        {
            float y = randFloat( topLeftFar.y, bottomRightFar.y );
            
            this->mPosition = vec3( topLeftFar.x - MARGIN, y, topLeftFar.z );
            this->speedPerSecond = vec3( randFloat( 4, 30 ), randFloat( -10, 10 ), randFloat( 4, 30 ) );
        }
            break;
            
        case 1:
        {
            float y = randFloat( topLeftFar.y, bottomRightFar.y );
            
            this->mPosition = vec3( bottomRightFar.x + MARGIN, y, topLeftFar.z );
            this->speedPerSecond = vec3( randFloat( -4, -30 ), randFloat( -10, 10 ), randFloat( 4, 30 ) );
        }
            break;
            
        case 2:
        {
            float y = randFloat( topLeftNear.y, bottomRightNear.y );
            
            this->mPosition = vec3( topLeftNear.x - MARGIN, y, topLeftNear.z );
            this->speedPerSecond = vec3( randFloat( 4, 30 ), randFloat( -10, 10 ), randFloat( -4, -30 ) );
        }
            break;
            
        case 3:
        {
            float y = randFloat( topLeftNear.y, bottomRightNear.y );
            
            this->mPosition = vec3( bottomRightNear.x + MARGIN, y, topLeftNear.z );
            this->speedPerSecond = vec3( randFloat( -4, -30 ), randFloat( -10, 10 ), randFloat( -4, -30 ) );
        }
            break;
            
        default: break;
    }
    
    this->tumbleAxis_ = vec3( randFloat( -1, 1 ), randFloat( -1, 1 ), randFloat( -1, 1 ) );
}

void Pyramid::update( vec3 topLeftNear, vec3 bottomRightNear, vec3 topLeftFar, vec3 bottomRightFar )
{
    this->topLeftNear = topLeftNear;
    this->bottomRightNear = bottomRightNear;
    this->topLeftFar = topLeftFar;
    this->bottomRightFar = bottomRightFar;
}

void Pyramid::update( float time, CameraPersp camera )
{
    if ( ! this->active ) return;
    
    tumbleAngle_ = tumbleAngle_ + ( tumbleSpeedPerSecond * time );
    
    if ( flashing_ )
    {
        ++counter_;
        if ( counter_ > FLASHING_COUNTER_MAX )
        {
            counter_ = 0;
            current_ = current_ + direction_;
            if ( current_ < 0 || current_ > slices.size() )
            {
                flashing_ = false;
            }
        }
    }
    else
    {
        if ( randFloat( 0.0f, 1000.0f ) > 998.0f )
        {
            flashing_ = true;
            direction_ = direction_ * -1;
            if ( direction_ > 0 )
            {
                current_ = 0;
            }
            else
            {
                current_ = slices.size() - 1;
            }
        }
    }
    
    if ( spinning_ > -1 )
    {
        ++spinningCounter_;
        if ( spinningCounter_ > SPIN_COUNTER_MAX ) spinning_ = -1;
    }
    else
    {
        if ( randFloat( 0.0f, 1000.0f ) > 900.0f )
        {
            spinning_ = randInt( 0, (slices.size()& INT_MAX) - 1 );
            spinningCounter_ = 0;
        }
    }
    
    mPosition = mPosition + ( speedPerSecond * time );
    
    vec2 positionOnScreen = camera.worldToScreen( mPosition, getWindowWidth(), getWindowHeight() );
    
    if ( positionOnScreen.x > -MARGIN && positionOnScreen.x < getWindowWidth() + MARGIN && positionOnScreen.y > -MARGIN && positionOnScreen.y < getWindowHeight() + MARGIN )
    {
        this->activated = true;
    }
    else
    {
        if ( this->activated )
        {
            mPosition = vec3( 0, 0, 500 );
            this->active = false;
            this->cue = timeline().add( std::bind( &Pyramid::start, this ), timeline().getCurrentTime() + randFloat( 5, 30 ) );
        }
    }
}

void Pyramid::draw()
{
    if ( ! this->active ) return;
    
    gl::pushModelMatrix();
    
    gl::translate( this->mPosition );
    gl::scale( 0.1, 0.1, 0.1 );
    gl::rotate( tumbleAngle_, tumbleAxis_ );
    
    for ( int i = 0; i < slices.size(); ++i )
    {
        if ( flashing_ && i == current_ )
        {
            gl::color( 1.0, 1.0, 1.0 );
        }
        else
        {
            gl::color( 0.937254901960784f, 0.105882352941176f, 0.203921568627451f );
        }
        
        if ( i == spinning_ )
        {
            gl::pushModelMatrix();
            gl::rotate( Tweening::easeInOutCubic( spinningCounter_, 0.0f, THIRD_OF_A_TURN, SPIN_COUNTER_MAX ), vec3( 0, 1, 0 ) );
        }
        
        slices[ i ]->draw();
        
        if ( i == spinning_ )
        {
            gl::popModelMatrix();
        }
    }
    
    gl::popModelMatrix();
}
