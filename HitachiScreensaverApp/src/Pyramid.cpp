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
    
//    auto sphere = geom::Sphere().subdivisions( 30 ).radius( 220 );
//    this->testSphere = gl::Batch::create( sphere, gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) );
    
    this->cue = timeline().add( std::bind( &Pyramid::start, this ), timeline().getCurrentTime() + randFloat( 5, 15 ) );
}

void Pyramid::update( Frustum f )
{
    this->f = f;
}

void Pyramid::start()
{
    this->active = true;
    this->activated = false;
    
    float z = randFloat( -300, - ENVIRONMENT_RADIUS );
    
    this->mPosition = vec3( 0, 0, z );
    
    direction dir = static_cast<direction>( randInt( 0, last ) );
    
    switch ( dir ) {
            
        case left:
        {
            while ( this->f.contains( this->mPosition, 22 ) ) this->mPosition = this->mPosition + vec3( - PROBE_STEP, 0, 0 );
            this->mPosition = this->mPosition + vec3( 1, 0, 0 );
            float y = this->mPosition.y;
            while ( this->f.contains( this->mPosition, 22 ) ) this->mPosition = this->mPosition + vec3( 0, PROBE_STEP, 0 );
            y = this->mPosition.y - y;
            this->mPosition = vec3( this->mPosition.x, randFloat( -y, y ), this->mPosition.z );
            while ( this->f.intersects( this->mPosition, 22 ) ) this->mPosition = this->mPosition + vec3( - PROBE_STEP, 0, 0 );
            
            this->speedPerSecond = vec3( randFloat( 4, 30 ), randFloat( -10, 10 ), randFloat( -5, 5 ) );
        }
            break;
            
        case right:
        {
            while ( this->f.contains( this->mPosition, 22 ) ) this->mPosition = this->mPosition + vec3( PROBE_STEP, 0, 0 );
            this->mPosition = this->mPosition + vec3( -1, 0, 0 );
            float y = this->mPosition.y;
            while ( this->f.contains( this->mPosition, 22 ) ) this->mPosition = this->mPosition + vec3( 0, PROBE_STEP, 0 );
            y = this->mPosition.y - y;
            this->mPosition = vec3( this->mPosition.x, randFloat( -y, y ), this->mPosition.z );
            while ( this->f.intersects( this->mPosition, 22 ) ) this->mPosition = this->mPosition + vec3( PROBE_STEP, 0, 0 );
            
            this->speedPerSecond = vec3( randFloat( -4, -30 ), randFloat( -10, 10 ), randFloat( -5, 5 ) );
        }
            break;
            
        case top:
        {
            while ( this->f.contains( this->mPosition, 22 ) ) this->mPosition = this->mPosition + vec3( 0, PROBE_STEP, 0 );
            this->mPosition = this->mPosition + vec3( 0, -1, 0 );
            float x = this->mPosition.x;
            while ( this->f.contains( this->mPosition, 22 ) ) this->mPosition = this->mPosition + vec3( PROBE_STEP, 0, 0 );
            x = this->mPosition.x - x;
            this->mPosition = vec3( randFloat( -x, x ), this->mPosition.y, this->mPosition.z );
            while ( this->f.intersects( this->mPosition, 22 ) ) this->mPosition = this->mPosition + vec3( 0, PROBE_STEP, 0 );
            
            this->speedPerSecond = vec3( randFloat( -10, 10 ), randFloat( -4, -30 ), randFloat( -5, 5 ) );
        }
            break;
            
        case bottom:
        {
            while ( this->f.contains( this->mPosition, 22 ) ) this->mPosition = this->mPosition + vec3( 0, - PROBE_STEP, 0 );
            this->mPosition = this->mPosition + vec3( 0, 1, 0 );
            float x = this->mPosition.x;
            while ( this->f.contains( this->mPosition, 22 ) ) this->mPosition = this->mPosition + vec3( PROBE_STEP, 0, 0 );
            x = this->mPosition.x - x;
            this->mPosition = vec3( randFloat( -x, x ), this->mPosition.y, this->mPosition.z );
            while ( this->f.intersects( this->mPosition, 22 ) ) this->mPosition = this->mPosition + vec3( 0, - PROBE_STEP, 0 );
            
            this->speedPerSecond = vec3( randFloat( -10, 10 ), randFloat( 4, 30 ), randFloat( -5, 5 ) );
        }
            break;
            
        default:
            
            throw new Exception( "Bad random direction for pyramid" );
            break;
    }
    
    this->tumbleAxis_ = vec3( randFloat( -1, 1 ), randFloat( -1, 1 ), randFloat( -1, 1 ) );
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
            spinning_ = randInt( 0, ( slices.size() & INT_MAX ) - 1 );
            spinningCounter_ = 0;
        }
    }
    
    mPosition = mPosition + ( speedPerSecond * time );
    
    if ( this->f.intersects( this->mPosition, 22 ) )
    {
        this->activated = true;
    }
    else
    {
        if ( this->activated )
        {
            this->active = false;
            mPosition = vec3( 0, 0, 500 );
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
    
    float distance = glm::distance( this->mPosition, vec3( 0, 0, -200 ) );
    
    distance = 0.5 + ( 0.5 * ( 1.0 - ( distance / 1100.0 ) ) );
    
    if ( distance > 1.0 ) distance = 1.0;
    
    for ( int i = 0; i < slices.size(); ++i )
    {
        if ( flashing_ && i == current_ )
        {
            gl::color( 1, 1, 1 );
        }
        else
        {
            gl::color( red * distance );
        }
        
        if ( i == spinning_ )
        {
            gl::pushModelMatrix();
            gl::rotate( Tweening::easeInOutCubic( spinningCounter_, 0, THIRD_OF_A_TURN, SPIN_COUNTER_MAX ), vec3( 0, 1, 0 ) );
        }
        
        slices[ i ]->draw();
        
        if ( i == spinning_ )
        {
            gl::popModelMatrix();
        }
    }
    
//    gl::color( 0, 1, 0 );
//    this->testSphere->draw();
    
    gl::popModelMatrix();
}
