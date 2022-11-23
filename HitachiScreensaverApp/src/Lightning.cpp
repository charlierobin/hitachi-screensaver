#include "Lightning.hpp"

Lightning::Lightning()
{
    this->shader = gl::getStockShader( gl::ShaderDef().color().texture() );
    
    gl::ContextRef backgroundCtx = gl::Context::create( gl::context() );
    
    this->m_Thread = std::shared_ptr<std::thread>( new std::thread( bind( &Lightning::threadMethod, this, backgroundCtx ) ) );
    
    CueRef nextLightningCue = timeline().add( std::bind( &Lightning::nextLightning, this ), timeline().getCurrentTime() + LIGHTNING_RANDOM_INTERVAL );
}

Lightning::~Lightning()
{
    this->m_ThreadShouldFinish = true;
    this->m_Frames->cancel();
    this->m_Thread->join();
}

void Lightning::nextLightning()
{
    this->m_NextPlease = true;
}

void Lightning::threadMethod( gl::ContextRef context )
{
    ci::ThreadSetup threadSetup;
    
    context->makeCurrent();
    
    while( ! this->m_ThreadShouldFinish )
    {
        if ( this->m_NextPlease )
        {
            this->m_NextPlease = false;
            this->m_Busy = true;
            
            int startFrame = randFloat( 0, MAX_FRAME_INDEX - MAX_LENGTH );
            
            int endFrame = startFrame + randFloat( MIN_LENGTH, MAX_LENGTH );
            
            m_Frames = new ConcurrentCircularBuffer<gl::TextureRef>( endFrame - startFrame + 1 );
            
            for ( int i = startFrame; i <= endFrame; i++ )
            {
                std::string str = std::to_string( i );
                
                if ( str.length() < ZEROS_PADDING ) str.insert( str.front() == '-' ? 1 : 0, ZEROS_PADDING - str.length(), '0' );
                
                std::string filename = "lightning_" + str + ".jpg";
                
                auto img = loadImage( loadResource( filename ) );
                
                auto texture = gl::Texture::create( img );
                
                auto fence = gl::Sync::create();
                fence->clientWaitSync();
                
                this->m_Frames->pushFront( texture );
            }
            
            if ( randInt( 2 ) > 0 )
            {
                this->x = X;
            }
            else
            {
                this->x = - X;
            }
            
            this->x = this->x + randFloat( X_VARIATION );
            
            if ( randInt( 2 ) > 0 )
            {
                this->flipX = 1;
            }
            else
            {
                this->flipX = -1;
            }
            
            this->rotation = randFloat( - ONE_DEGREE * 5, ONE_DEGREE * 5 );
            
            this->m_Done = true;
        }
        else
        {
            std::chrono::milliseconds duration( 100 );
            std::this_thread::sleep_for( duration );
        }
    }
}

void Lightning::update()
{
    if ( this->m_Done )
    {
        this->m_Done = false;
        this->m_Frames->popBack( &this->m_Frame );
    }
}

void Lightning::draw()
{
    if ( this->m_Frame )
    {
        this->shader->bind();
        
        this->m_Frame->bind();
        
        gl::color( 1, 1, 1 );
        
        gl::disableDepthRead();
        gl::disableDepthWrite();
        
        gl::disableAlphaBlending();
        gl::enableAdditiveBlending();
        
        gl::drawBillboard( vec3( this->x, 0, -LIGHTNING_Z ), vec2( 60, 110 ), this->rotation, vec3( this->flipX, 0, 0 ), vec3( 0, -1, 0 ) );

        gl::enableAlphaBlending();
        
        gl::enableDepth();
        
        if ( this->m_Frames->getSize() > 0 )
        {
            this->m_Frames->popBack( &this->m_Frame );
        }
        else
        {
            this->m_Frame = nil;
            this->m_Busy = false;
            CueRef nextLightningCue = timeline().add( std::bind( &Lightning::nextLightning, this ), timeline().getCurrentTime() + LIGHTNING_RANDOM_INTERVAL );
        }
    }
}

