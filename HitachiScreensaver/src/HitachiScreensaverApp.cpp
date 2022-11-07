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
    
    Sun * sun;
    Starfield * starfield;
    LensFlare * flare;
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
    
    
    
    

    
    
    
    this->pyramids.push_back( new Pyramid( vec3( -10, -10, -100 ), vec3( 1, 0, 0 ) ) );
    this->pyramids.push_back( new Pyramid( vec3( 10, 10, -200 ), vec3( -2, 0, 0 ) ) );
    
    
    
    
    
    
    this->heroPyramid = new HeroPyramid();
    
    this->flare = new LensFlare();
    this->sun = new Sun();
    this->lightning = new Lightning();
    
    this->lastTimeSample = std::chrono::high_resolution_clock::now();
}

void HitachiScreensaverApp::resize()
{
    this->camera.setAspectRatio( this->getWindowAspectRatio() );
}

void HitachiScreensaverApp::update()
{
    chrono::high_resolution_clock::time_point thisTimeSample = chrono::high_resolution_clock::now();
    float nanoseconds = chrono::duration_cast<chrono::nanoseconds>( thisTimeSample - this->lastTimeSample ).count();
    float seconds = nanoseconds / 1E+09;
    
    this->lastTimeSample = thisTimeSample;
    
    this->starfield->update( seconds );
    for ( int i = 0; i < this->placards.size(); ++i ) this->placards[ i ]->update( seconds );
    for ( int i = 0; i < this->pyramids.size(); ++i ) this->pyramids[ i ]->update( seconds, this->pyramids, i );
    this->heroPyramid->update( seconds );
    this->sun->update( seconds, camera );
    
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
    
//    this->starfield->draw();
//    this->sun->draw();
//    for ( int i = 0; i < this->placards.size(); ++i ) this->placards[ i ]->draw();
//    for ( int i = 0; i < this->pyramids.size(); ++i ) this->pyramids[ i ]->draw();

//    this->lightning->draw();
    
//    this->heroPyramid->draw();
    
    
    
//    this->flare->position = this->sun->sunPositionOnScreen;
    
    
    float scaledX = flare->position.x * this->getWindowContentScale();
    float scaledY = flare->position.y * this->getWindowContentScale();
    
    Surface s = this->copyWindowSurface( Area( scaledX, scaledY, scaledX + 1, scaledY + 1 ) );
    
    int yellowCount = 0;

    ColorA c = s.getPixel( vec2( 0, 0 ) );
    
    if ( c.r == 1 && c.g == 1 && c.b == 0 ) ++yellowCount;
    
    this->flare->intensity = yellowCount;
    
//    this->flare->draw();
    
//    gl::setMatricesWindow( this->getWindowSize() );
    
    
    
    
    mat4 projection = this->camera.getProjectionMatrix() * this->camera.getViewMatrix();


    vec4 viewport = vec4( 0, getWindowHeight(), getWindowWidth(), -getWindowHeight() );

    vec3 worldCoordinate = unProject( vec3( getWindowWidth(), getWindowHeight(), 0.9999 ), mat4(), projection, viewport );
    
    cout << worldCoordinate << endl;
    
    
    worldCoordinate = unProject( vec3( getWindowWidth(), getWindowHeight(), 0.9991 ), mat4(), projection, viewport );
    
    cout << worldCoordinate << endl;
    
    
    
    gl::context()->getStockShader( gl::ShaderDef().color() )->bind();

    gl::color( 0, 1, 0 );

    gl::pushModelMatrix();

//    worldCoordinate = vec3( 0, 0, -100 );
    
    gl::drawSphere( worldCoordinate, 0.1 );

    gl::popModelMatrix();
    
}

CINDER_APP( HitachiScreensaverApp, RendererGl( RendererGl::Options().msaa( 1 ) ), [&]( App::Settings *settings )
{
    settings->setHighDensityDisplayEnabled();
//    settings->setWindowSize( 640 * 2, 480 * 2 );
})
