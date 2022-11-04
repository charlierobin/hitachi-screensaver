#ifndef Lightning_hpp
#define Lightning_hpp

using namespace ci;
using namespace ci::app;

class Lightning
{
    
public:
    
    Lightning();
    
    void update();
    void draw();
    
private:
    
    gl::TextureRef texture;
    
};

#endif /* Lightning_hpp */
