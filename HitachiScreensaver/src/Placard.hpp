#ifndef Placard_hpp
#define Placard_hpp

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/ObjLoader.h"

#include "cinder/Rand.h"

#include "macros.h"
#include "IItem.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class Placard: public IItem
{
    
public:
    
    Placard();
    
    void initialise();
    void loadTexture( string );
    
    void randomise();
    void setSpeed( float );
    
    void update( float, std::vector<IItem *>, int ) override;
    void draw( bool ) override;
    
protected:
    
    cinder::gl::BatchRef placard_;
    
    float angle_ = 0.0;
    float speedPerSecond_ = ONE_TURN / 25.0f;
    
    float zRotation_ = 0.0f;
    float yRotation_ = 0.0f;
    
    gl::Texture2dRef texture_;
    ColorA colour_ = ColorA( 1.0, 1.0, 1.0, 0.5 );
};

#endif /* Placard_hpp */
