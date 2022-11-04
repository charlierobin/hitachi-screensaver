#include "Pyramid.hpp"

Pyramid::Pyramid()
{
    ObjLoader loader( loadResource( "pyramid.obj" ) );
    
    this->slices_.push_back( gl::Batch::create( loader.groupName( "Obj1" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    this->slices_.push_back( gl::Batch::create( loader.groupName( "Obj2" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    this->slices_.push_back( gl::Batch::create( loader.groupName( "Obj3" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    this->slices_.push_back( gl::Batch::create( loader.groupName( "Obj4" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    this->slices_.push_back( gl::Batch::create( loader.groupName( "Obj5" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    this->slices_.push_back( gl::Batch::create( loader.groupName( "Obj6" ), gl::context()->getStockShader( gl::ShaderDef().lambert().color() ) ) );
    
    this->maskSlices.push_back( gl::Batch::create( loader.groupName( "Obj1" ), gl::context()->getStockShader( gl::ShaderDef().color() ) ) );
    this->maskSlices.push_back( gl::Batch::create( loader.groupName( "Obj2" ), gl::context()->getStockShader( gl::ShaderDef().color() ) ) );
    this->maskSlices.push_back( gl::Batch::create( loader.groupName( "Obj3" ), gl::context()->getStockShader( gl::ShaderDef().color() ) ) );
    this->maskSlices.push_back( gl::Batch::create( loader.groupName( "Obj4" ), gl::context()->getStockShader( gl::ShaderDef().color() ) ) );
    this->maskSlices.push_back( gl::Batch::create( loader.groupName( "Obj5" ), gl::context()->getStockShader( gl::ShaderDef().color() ) ) );
    this->maskSlices.push_back( gl::Batch::create( loader.groupName( "Obj6" ), gl::context()->getStockShader( gl::ShaderDef().color() ) ) );
    
    auto sphere = geom::Sphere().subdivisions( 30 ).radius( physicsRadius );
    
    collisionSphere = gl::Batch::create( sphere, gl::context()->getStockShader( gl::ShaderDef().color() ) );
    
    this->mPosition = vec3( 0, 0, -100 );
    this->speedPerSecond = vec3( 6, 0, 0 );
}

Pyramid::Pyramid( vec3 position, vec3 speed ) : Pyramid()
{
    this->mPosition = position;
    this->speedPerSecond = speed;
}

void Pyramid::update( float time, std::vector<IItem *> items, int index )
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
    
    for ( int i = index + 1; i < items.size(); ++i )
    {
        if(std::is_class<Pyramid>::value)
        {
            Pyramid* p = dynamic_cast<Pyramid*>( items[ i ] );
            
            float distance = glm::distance( this->mPosition, p->mPosition );
            
            if ( distance <= ( physicsDiameter ) )
            {
                this->speedPerSecond = this->speedPerSecond * vec3( -1, 0, 0 );
                p->speedPerSecond = p->speedPerSecond * vec3( -1, 0, 0 );
            }
        }
    }
    
    float distanceFromCentre = glm::distance( this->mPosition, vec3( 0, 0, 0 ) );
    
    if ( distanceFromCentre > ENVIRONMENT_COLLISION_RADIUS )
    {
        this->speedPerSecond = this->speedPerSecond * vec3( -1, -1, -1 );
    }
    
    mPosition = mPosition + ( speedPerSecond * time );
}

void Pyramid::draw( bool mask )
{
    gl::pushModelMatrix();
    
    gl::translate( this->mPosition );
    gl::scale( 0.1, 0.1, 0.1 );
    gl::rotate( tumbleAngle_, tumbleAxis_ );
    
    if ( mask )
    {
        gl::color( 0, 0, 0 );
        collisionSphere->draw();
    }
    else
    {
        for ( int i = 0; i < slices_.size(); ++i )
        {
            if ( mask )
            {
                gl::color( 1.0, 1.0, 1.0 );
            }
            else
            {
                if ( flashing_ && i == current_ )
                {
                    gl::color( 1.0, 1.0, 1.0 );
                }
                else
                {
                    gl::color( 0.937254901960784f, 0.105882352941176f, 0.203921568627451f );
                }
            }
            
            if ( i == spinning_ )
            {
                gl::pushModelMatrix();
                gl::rotate( Tweening::easeInOutCubic( spinningCounter_, 0.0f, THIRD_OF_A_TURN, SPIN_COUNTER_MAX ), vec3( 0, 1, 0 ) );
            }
            
            if ( mask )
            {
                 this->maskSlices[ i ]->draw();
            }
            else
            {
                slices_[ i ]->draw();
            }
            
            if ( i == spinning_ )
            {
                gl::popModelMatrix();
            }
        }
    }
    
    //    cinder::gl::color( 0.0, 1.0, 0.0 );
    //    collisionSphere->draw();
    
    gl::popModelMatrix();
}
