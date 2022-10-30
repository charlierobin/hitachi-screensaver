#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "Pyramid.hpp"
#include "Starfield.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class HitachiScreensaverApp : public App
{
public:
    void setup() override;
    void update() override;
    void draw() override;
    void resize() override;
    
private:
    
    CameraPersp mCamera;
    chrono::high_resolution_clock::time_point mLastTimeSample;
    vector<IItem *> mItems;
};

void HitachiScreensaverApp::setup()
{
    Rand::randomize();
    
    this->mCamera.setEyePoint(CAMERA_POSITION);
    this->mCamera.lookAt(CENTRE_OF_THE_WORLD);
    
    this->mCamera.setFarClip( FAR_CLIP );
    
    mItems.push_back( new Starfield() );
    
    mItems.push_back( new Pyramid() );
    
    mLastTimeSample = std::chrono::high_resolution_clock::now();
}

void HitachiScreensaverApp::resize()
{
    this->mCamera.setAspectRatio(this->getWindowAspectRatio());
}

void HitachiScreensaverApp::update()
{
    chrono::high_resolution_clock::time_point thisTimeSample = chrono::high_resolution_clock::now();
    float nanoseconds = chrono::duration_cast<chrono::nanoseconds>( thisTimeSample - mLastTimeSample ).count();
    float seconds = nanoseconds / 1E+09;
    
    mLastTimeSample = thisTimeSample;
    
    for ( int i = 0; i < mItems.size(); ++i )
    {
        mItems[ i ]->update( seconds );
    }
    
    int fps = 1 / seconds;
    
    this->getWindow()->setTitle(to_string(fps));
}

void HitachiScreensaverApp::draw()
{
    gl::clear();
    
    gl::enableDepthRead();
    gl::enableDepthWrite();
    
    gl::setMatrices( this->mCamera );
    
    for ( int i = 0; i < mItems.size(); ++i )
    {
        mItems[ i ]->draw();
    }
    
    gl::setMatricesWindow( getWindowSize() );
}

CINDER_APP( HitachiScreensaverApp, RendererGl )
