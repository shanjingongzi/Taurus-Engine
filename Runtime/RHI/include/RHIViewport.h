#pragma once
#include "RHIResource.h"

class RHIViewport:public RHIResource
{
public:
    RHIViewport():RHIResource(ERHIResourceType::RRT_Viewport){}

    virtual void *GetNativeSwapChain()const{return nullptr;}

    virtual void*GetNativeBackBufferTexture()const{return nullptr;}

    virtual void *GetNativeWindow(void **addParam=nullptr)const{return nullptr;}

    virtual void SetCustomPresent(class RHICustomPresent *){}

    virtual class RHICustomPresent* GetCustomPresent()const{return nullptr;}

    virtual void Tick(float deltaTime){}

    virtual void WaitForFrameEventCompletion(){}

    virtual void IssueFrameEvent(){}
private:

};