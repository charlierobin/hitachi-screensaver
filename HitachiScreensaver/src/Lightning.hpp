#ifndef Lightning_hpp
#define Lightning_hpp

#include "cinder/ConcurrentCircularBuffer.h"
#include "cinder/Timeline.h"
#include "cinder/Rand.h"

#include "macros.h"

using namespace ci;
using namespace ci::app;

class Lightning
{
    
public:
    
    Lightning();
    ~Lightning();
    
    void update();
    void draw();
    
private:
    
    void threadMethod( gl::ContextRef sharedGlContext );
    void nextLightning();
    
    std::shared_ptr<std::thread> m_Thread;
    
    cinder::gl::GlslProgRef shader;
    
    ConcurrentCircularBuffer<gl::TextureRef> *m_Frames;
    gl::TextureRef m_Frame;
    
    bool m_Busy;
    bool m_NextPlease;
    bool m_Done;
    bool m_ThreadShouldFinish;
    
    float flipX = 1;
    float x;
    float rotation;
};

#define MAX_FRAME_INDEX 249

#define MIN_LENGTH 8
#define MAX_LENGTH 20

#define ZEROS_PADDING 3

#define LIGHTNING_RANDOM_INTERVAL randFloat( 15, 45 )

#define X 60
#define X_VARIATION -10, 10

#endif /* Lightning_hpp */
