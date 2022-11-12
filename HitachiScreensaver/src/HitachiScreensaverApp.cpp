#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "HeroPyramid.hpp"
#include "Pyramid.hpp"
#include "Starfield.hpp"
#include "Sun.hpp"
#include "HitachiLensFlare.hpp"
#include "HitachiPlacard.hpp"
#include "HiCommandPlacard.hpp"
#include "CaptionPlacard.hpp"
#include "Lightning.hpp"

#define NUMBER_OF_LITTLE_PYRAMIDS 20
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
    
    Starfield * starfield;
    HitachiLensFlare * flare;
    Sun * sun;
    Lightning * lightning;
    
    vector<Placard *> placards;
    vector<Pyramid *> pyramids;
    
    HeroPyramid * heroPyramid;
    
    chrono::high_resolution_clock::time_point lastTimeSample;
    int counter = 0;
    int fps = 0;
};

void HitachiScreensaverApp::setup()
{
    this->setFrameRate( 60 );
    
    Rand::randomize();
    
    this->camera.setEyePoint( CAMERA_POSITION );
    this->camera.lookAt( CENTRE_OF_THE_WORLD );
    
    this->camera.setFarClip( FAR_CLIP );
    
    this->starfield = new Starfield();
    
    for ( int i = 0; i < NUMBER_OF_LOGOS; ++i ) this->placards.push_back( new HitachiPlacard() );
    for ( int i = 0; i < NUMBER_OF_HICOMMANDS; ++i ) this->placards.push_back( new HiCommandPlacard() );
    for ( int i = 0; i < NUMBER_OF_CAPTIONS; ++i ) this->placards.push_back( new CaptionPlacard() );
    
    this->heroPyramid = new HeroPyramid();
    
    this->flare = new HitachiLensFlare();
    this->sun = new Sun();
    this->lightning = new Lightning();
    
    this->lastTimeSample = std::chrono::high_resolution_clock::now();
}

void HitachiScreensaverApp::resize()
{
    this->camera.setAspectRatio( this->getWindowAspectRatio() );
    
    Frustum f = Frustum( this->camera );
    
    for ( int i = 0; i < this->pyramids.size(); ++i ) this->pyramids[ i ]->update( f );
    
    this->flare->axis = getWindowCenter();
}

void HitachiScreensaverApp::update()
{
    Frustum f = Frustum( this->camera );
    
    if ( this->pyramids.size() == 0 )
    {
        for ( int i = 0; i < NUMBER_OF_LITTLE_PYRAMIDS; ++i )
        {
            this->pyramids.push_back( new Pyramid() );
        }
        
        for ( int i = 0; i < this->pyramids.size(); ++i ) this->pyramids[ i ]->update( f );
    }
    
    chrono::high_resolution_clock::time_point thisTimeSample = chrono::high_resolution_clock::now();
    float nanoseconds = chrono::duration_cast<chrono::nanoseconds>( thisTimeSample - this->lastTimeSample ).count();
    float seconds = nanoseconds / 1E+09;
    
    this->lastTimeSample = thisTimeSample;
    
    this->starfield->update( seconds );
    this->lightning->update();
    
    for ( int i = 0; i < this->placards.size(); ++i ) this->placards[ i ]->update( seconds );
    for ( int i = 0; i < this->pyramids.size(); ++i ) this->pyramids[ i ]->update( seconds, this->camera );
    this->heroPyramid->update( seconds );
    this->sun->update( seconds, this->camera );
    
    this->flare->update();
    
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
    gl::setMatrices( this->camera );
    
    gl::enableDepthRead();
    gl::enableDepthWrite();
    
    gl::clear();
    
    this->starfield->draw();
    
    for ( int i = 0; i < this->placards.size(); ++i ) this->placards[ i ]->draw();
    
    
    this->lightning->draw();
    
    
    this->sun->draw();
    
    
    for ( int i = 0; i < this->pyramids.size(); ++i ) this->pyramids[ i ]->draw();
    
    
    this->heroPyramid->draw();
    
    this->flare->position = this->sun->positionOnScreen;
    this->flare->onScreen = this->sun->onScreen;
    
    float scaledX = flare->position.x * this->getWindowContentScale();
    float scaledY = flare->position.y * this->getWindowContentScale();
    
    Surface s = this->copyWindowSurface( Area( scaledX - 2, scaledY - 2, scaledX + 2, scaledY + 2 ) );
    
    float yellowCount = 0;
    
    Surface::Iter iter = s.getIter();
    
    float total = iter.getWidth() * iter.getHeight();
    
    total = 16;
    
    while( iter.line() ) {
       while( iter.pixel() ) {
           if ( iter.r() == 255 && iter.g() == 255 && iter.b() == 0 ) ++yellowCount;
       }
    }
    
    this->flare->intensity = yellowCount / total;
    
//    cout << this->flare->intensity << endl;
    
    this->flare->draw();
}

CINDER_APP( HitachiScreensaverApp, RendererGl( RendererGl::Options().msaa( 1 ) ), [&]( App::Settings *settings )
{
    settings->setHighDensityDisplayEnabled();
    settings->setWindowSize( 1920, 1080 );
//    settings->setWindowSize( 1280, 720 );
} )
