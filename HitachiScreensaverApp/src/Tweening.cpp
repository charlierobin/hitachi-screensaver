#include "Tweening.hpp"

float Tweening::quart( float t_CurrentTime, float b_BeginningValue, float c_ToAddToBeginningToGetFinal, float d_TotalTime )
{
    if ((t_CurrentTime/=d_TotalTime/2) < 1) return c_ToAddToBeginningToGetFinal/2*t_CurrentTime*t_CurrentTime*t_CurrentTime*t_CurrentTime + b_BeginningValue;
    
    float blah = t_CurrentTime-=2;
    
    return -c_ToAddToBeginningToGetFinal/2*(blah*t_CurrentTime*t_CurrentTime*t_CurrentTime - 2) + b_BeginningValue;
    
}

float Tweening::easeInOutCubic( float t_CurrentTime, float b_BeginningValue, float c_ToAddToBeginningToGetFinal, float d_TotalTime )
{
    if ((t_CurrentTime/=d_TotalTime/2) < 1) return c_ToAddToBeginningToGetFinal/2*t_CurrentTime*t_CurrentTime*t_CurrentTime + b_BeginningValue;
    
    float blah = t_CurrentTime-=2;
    
    return c_ToAddToBeginningToGetFinal/2*(blah*t_CurrentTime*t_CurrentTime + 2) + b_BeginningValue;
}

float Tweening::easeOutCubic( float t_CurrentTime, float b_BeginningValue, float c_ToAddToBeginningToGetFinal, float d_TotalTime )
{
    
    float blah = t_CurrentTime=t_CurrentTime/d_TotalTime-1;
    
    return c_ToAddToBeginningToGetFinal*((blah)*t_CurrentTime*t_CurrentTime + 1) + b_BeginningValue;
    
}

float Tweening::easeInCubic( float t_CurrentTime, float b_BeginningValue, float c_ToAddToBeginningToGetFinal, float d_TotalTime )
{
    
    float blah = t_CurrentTime/=d_TotalTime;
    
    return c_ToAddToBeginningToGetFinal*(blah)*t_CurrentTime*t_CurrentTime + b_BeginningValue;
    
}


