#ifndef HeroPyramidSlice_hpp
#define HeroPyramidSlice_hpp

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Timeline.h"
#include "cinder/ObjLoader.h"

#include "macros.h"
#include "Tweening.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class HeroPyramidSlice
{
    
public:
    
    HeroPyramidSlice( string, float );
    
    void update( float );
    void draw();
    
    void trigger( float );
    
    void startComingIn();
    void startGoingOut();
    
    bool isBusy();
    
private:
    
    float x_ = 0.0f;
    float y_ = 0.0f;
    float z_ = 0.0f;
    
    cinder::gl::BatchRef batchRef_;
    float angle_ = 0.0;
    int counter_ = 0;
    
    enum states_ { OFF_SCREEN, COMING_IN, ON_SCREEN, GOING_OUT };
    states_ state_ = OFF_SCREEN;
    
    bool busy_ = false;
    
    float offset_ = 0.0f;
    float duration_;
};

#define COMING_IN_COUNTER_MAX 150
#define GOING_OUT_COUNTER_MAX 100

#define AROUND_Y_AXIS cinder::vec3( 0, 1, 0 )

#endif /* HeroPyramidSlice_hpp */
