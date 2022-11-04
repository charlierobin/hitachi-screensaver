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
#include "Lightning.hpp"

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
    
private:
    
    CameraPersp camera;
    chrono::high_resolution_clock::time_point lastTimeSample;
    vector<IItem *> items;
    Sun * sun;
    Surface renderedMask;
    LensFlare * flare;
    Lightning * lightning;
    
    int counter = 0;
    int fps = 0;
    
    gl::FboRef buffer;
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
//    for ( int i = 0; i < NUMBER_OF_CAPTIONS; ++i ) this->items.push_back( new CaptionPlacard() );
    
    this->items.push_back( new Pyramid( vec3( 40, 0, -100 ), vec3( -6, 0, 0 ) ) );
    this->items.push_back( new Pyramid( vec3( -40, 0, -100 ), vec3( 6, 0, 0 ) ) );
    
    //    this->items.push_back( new HeroPyramid() );
    
//    this->flare = new LensFlare();
//    this->sun = new Sun();
//    this->lightning = new Lightning();
    
    this->lastTimeSample = std::chrono::high_resolution_clock::now();
}

void HitachiScreensaverApp::resize()
{
    this->camera.setAspectRatio( this->getWindowAspectRatio() );
    this->buffer = gl::Fbo::create( 640 * this->getWindowContentScale(), 480 * this->getWindowContentScale() );
}

void HitachiScreensaverApp::update()
{
    chrono::high_resolution_clock::time_point thisTimeSample = chrono::high_resolution_clock::now();
    float nanoseconds = chrono::duration_cast<chrono::nanoseconds>( thisTimeSample - this->lastTimeSample ).count();
    float seconds = nanoseconds / 1E+09;
    
    this->lastTimeSample = thisTimeSample;
    
    for ( int i = 0; i < this->items.size(); ++i ) this->items[ i ]->update( seconds, this->items, i );

//    this->sun->update( seconds, camera );
    
    this->counter++;
    
    if ( this->counter > 60 )
    {
        this->counter = 0;
        this->fps = 1 / seconds;
    }
    
    this->getWindow()->setTitle( to_string( this->fps ) );
}

void HitachiScreensaverApp::draw()
{
    this->buffer->bindFramebuffer();
    
    

    
    gl::setMatrices( this->camera );
    
    gl::enableDepthRead();
    gl::enableDepthWrite();
    
    gl::clear( Color( 1, 1, 1 ) );
    
    for ( int i = 0; i < this->items.size(); ++i ) this->items[ i ]->draw( true );
    
    gl::setMatricesWindow( this->getWindowSize() );
    
    this->buffer->unbindFramebuffer();

    


    
    gl::setMatrices( this->camera );
    
    gl::enableDepthRead();
    gl::enableDepthWrite();
    
    gl::clear();
    
    for ( int i = 0; i < this->items.size(); ++i ) this->items[ i ]->draw( false );

//    this->sun->draw();
//    this->flare->draw( false );
//    this->lightning->draw();
    
    gl::setMatricesWindow( this->getWindowSize() );
    
    gl::color( 1, 1, 1 );
    
    gl::draw( this->buffer->getColorTexture(), this->buffer->getBounds(), Rectf( 50, 50, 100, 100 ) );
}

CINDER_APP( HitachiScreensaverApp, RendererGl( RendererGl::Options().msaa( 2 ) ), [&]( App::Settings *settings )
{
    settings->setHighDensityDisplayEnabled();
    settings->setWindowSize( 640, 480 );
})
