#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "HeroPyramid.hpp"
#include "Pyramid.hpp"
#include "Starfield.hpp"
#include "Sun.hpp"
#include "LensFlare.hpp"
#include "HitachiPlacard.hpp"
#include "HiCommandPlacard.hpp"
#include "CaptionPlacard.hpp"

#define NUMBER_OF_LITTLE_PYRAMIDS 100
#define NUMBER_OF_LOGOS 2
#define NUMBER_OF_HICOMMANDS 2
#define NUMBER_OF_CAPTIONS 2

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
    
    void mouseDown( MouseEvent event ) override;
    
private:
    
    CameraPersp camera;
    chrono::high_resolution_clock::time_point lastTimeSample;
    vector<IItem *> items;
    Sun * sun;
    Surface renderedMask;
    LensFlare * flare;
    
    int counter = 0;
};

void HitachiScreensaverApp::setup()
{
    this->setFrameRate( 60 );
    
    Rand::randomize();
    
    this->camera.setEyePoint( CAMERA_POSITION );
    this->camera.lookAt( CENTRE_OF_THE_WORLD );
    
    this->camera.setFarClip( FAR_CLIP );
    
    this->items.push_back( new Starfield() );
    
//    for ( int i = 0; i < NUMBER_OF_LOGOS; ++i ) this->items.push_back( new HitachiPlacard() );
//    for ( int i = 0; i < NUMBER_OF_HICOMMANDS; ++i ) this->items.push_back( new HiCommandPlacard() );
    for ( int i = 0; i < NUMBER_OF_CAPTIONS; ++i ) this->items.push_back( new CaptionPlacard() );
    
//    this->items.push_back( new Pyramid( vec3( 40, 0, -100 ), vec3( -6, 0, 0 ) ) );
//    this->items.push_back( new Pyramid( vec3( -40, 0, -100 ), vec3( 6, 0, 0 ) ) );
    
    //    this->items.push_back( new HeroPyramid() );
    
    flare = new LensFlare();
    sun = new Sun();
    
    this->lastTimeSample = std::chrono::high_resolution_clock::now();
}

void HitachiScreensaverApp::resize()
{
    this->camera.setAspectRatio( this->getWindowAspectRatio() );
}

void HitachiScreensaverApp::mouseDown( MouseEvent event )
{
    this->flare->position = event.getPos();
}

void HitachiScreensaverApp::update()
{
    chrono::high_resolution_clock::time_point thisTimeSample = chrono::high_resolution_clock::now();
    float nanoseconds = chrono::duration_cast<chrono::nanoseconds>( thisTimeSample - this->lastTimeSample ).count();
    float seconds = nanoseconds / 1E+09;
    
    this->lastTimeSample = thisTimeSample;
    
    for ( int i = 0; i < this->items.size(); ++i ) this->items[ i ]->update( seconds, this->items, i );

    this->sun->update( seconds, camera );
    
    this->counter++;
    
    if ( this->counter > 60 )
    {
        this->counter = 0;
        int fps = 1 / seconds;
        this->getWindow()->setTitle( to_string( fps ) );
    }
}

void HitachiScreensaverApp::draw()
{
    gl::setMatrices( this->camera );
    
    gl::enableDepthRead();
    gl::enableDepthWrite();
    
    // render mask for lens flare
    
    gl::clear();
    
    for ( int i = 0; i < this->items.size(); ++i ) this->items[ i ]->draw( true );

    this->renderedMask = this->copyWindowSurface();
    
    this->flare->position = this->sun->sunPositionOnScreen_;
    
    float average = 0;
    
    float scaledX = flare->position.x * this->getWindowContentScale();
    float scaledY = flare->position.y * this->getWindowContentScale();
    
    average = average + this->renderedMask.getPixel( vec2( scaledX, scaledY ) ).r;
    
    average = average + this->renderedMask.getPixel( vec2( scaledX - 1, scaledY ) ).r;
    average = average + this->renderedMask.getPixel( vec2( scaledX + 1, scaledY ) ).r;
    average = average + this->renderedMask.getPixel( vec2( scaledX - 2, scaledY ) ).r;
    average = average + this->renderedMask.getPixel( vec2( scaledX + 2, scaledY ) ).r;

    average = average + this->renderedMask.getPixel( vec2( scaledX, scaledY - 1 ) ).r;
    average = average + this->renderedMask.getPixel( vec2( scaledX, scaledY + 1 ) ).r;
    average = average + this->renderedMask.getPixel( vec2( scaledX, scaledY - 2 ) ).r;
    average = average + this->renderedMask.getPixel( vec2( scaledX, scaledY + 2 ) ).r;

    average = average / 9;
    
    this->flare->intensity = ( 255 - average ) / 255;
    
    // render beauty pass
    
    gl::clear();
    
    for ( int i = 0; i < this->items.size(); ++i ) this->items[ i ]->draw( false );

    this->sun->draw();
    
    this->flare->draw( false );
    
    gl::setMatricesWindow( this->getWindowSize() );
}

CINDER_APP( HitachiScreensaverApp, RendererGl( RendererGl::Options().msaa( 2 ) ), [&]( App::Settings *settings )
{
    settings->setWindowSize( 1280, 720 );
    settings->setHighDensityDisplayEnabled();
})
