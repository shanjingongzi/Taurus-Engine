#pragma once
#include "RHIResource.h"

class RHIViewport
{
public:
    RHIViewport():RHIResource(RRI_Viewport){}

    virtual void *GetNativeSwapChain()const{return nullptr;}

    virtual void*GetNativeBackBufferTexture()const{return nullptr;}

    virtual void *GetNativeWindow(void **addParam=nullptr)const{return nullptr;}

    virtual void SetCustomPresent(class RHICustomPresent *){}

    virtual class RHICustomPresent* GetCustomPresent()const{return nullptr;}

    virtual Tick(float deltaTime){}

    virtual WaitForFrameEventCompletion(){}

    virtual void IssueFrameEvent(){}
    
private:

};