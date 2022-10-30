#include "Pyramid.hpp"

Pyramid::Pyramid()
{
    ObjLoader loader( loadResource( "pyramid.obj" ) );
    
    slices_.push_back( gl::Batch::create( loader.groupName( "Obj1" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    slices_.push_back( gl::Batch::create( loader.groupName( "Obj2" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    slices_.push_back( gl::Batch::create( loader.groupName( "Obj3" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    slices_.push_back( gl::Batch::create( loader.groupName( "Obj4" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    slices_.push_back( gl::Batch::create( loader.groupName( "Obj5" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    slices_.push_back( gl::Batch::create( loader.groupName( "Obj6" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    
    this->mPosition = vec3(0,0,-100);
    this->speedPerSecond = vec3(6,0,0);
}

void Pyramid::update( float time )
{
    if ( flashing_ )
    {
        ++counter_;
        if ( counter_ > FLASHING_COUNTER_MAX )
        {
            counter_ = 0;
            current_ = current_ + direction_;
            if ( current_ < 0 || current_ > slices_.size() )
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
                current_ = slices_.size() - 1;
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
            spinning_ = randInt( 0, (slices_.size()& INT_MAX) - 1 );
            spinningCounter_ = 0;
        }
    }
    
    mPosition = mPosition + ( speedPerSecond * time );
}

void Pyramid::draw()
{
    gl::pushModelMatrix();
    
    gl::translate( this->mPosition );
    gl::scale( 0.1, 0.1, 0.1 );
    //    gl::rotate( tumbleAngle_, tumbleAxis_ );
    
    for ( int i = 0; i < slices_.size(); ++i )
    {
        if ( flashing_ && i == current_ )
        {
            cinder::gl::color( 1.0, 1.0, 1.0, 1.0 );
        }
        else
        {
            cinder::gl::color( 239.0f / 255.0f, 27.0f / 255.0f, 52.0f / 255.0f, 1.0 );
        }
        
        if ( i == spinning_ )
        {
            gl::pushModelMatrix();
            gl::rotate( Tweening::easeInOutCubic( spinningCounter_, 0.0f, THIRD_OF_A_TURN, SPIN_COUNTER_MAX ), vec3( 0, 1, 0 ) );
        }
        
        slices_[ i ]->draw();
        
        if ( i == spinning_ )
        {
            gl::popModelMatrix();
        }
    }
    
    gl::popModelMatrix();
}


