#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HitachiScreensaverApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void HitachiScreensaverApp::setup()
{
}

void HitachiScreensaverApp::mouseDown( MouseEvent event )
{
}

void HitachiScreensaverApp::update()
{
}

void HitachiScreensaverApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( HitachiScreensaverApp, RendererGl )
