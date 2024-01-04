#pragma once
#include "RenderTarget.h"
#include "RenderResource.h"
class  Viewport:public RenderTarget,protected RenderResource
{
public:
    static OnViewportResized ViewportResizedEvent;
    Viewport(ViewportClient *inViewportClient );
    virtual ~Viewport();
    virtual void Destroy()=0;
    //begin viepwort interface
    virtual void *GetWindow()=0;
    virtual void MoveWindow(int32 newPosx,int32 newPosy,int32 newSizeX,int newSizeY);

    virtual void BeginRenderFrame(RHICommandListImmediate &RHICmdList);

    virtual void EndRenderFrame(RHICommandListImmediate &RHICmdList,bool present,bol lockToVsync);

    virtual void Draw(bool shouldPresent=true);

    ViewportClient GetClient()const{return viewportClient;}
private:
    ViewportClient *client;
    
}