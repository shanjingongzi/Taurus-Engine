#pragma once
#include <RHIViewport.h>
#include "VulkanMemory.h"
class VulkanViewport:public RHIViewport,public VulkanRHI::DeviceChild
{
public:
    enum{ NUM_BUFFERS=3};

    VulkanViewport(VulkanDevice *device,void *windowHandle,uint32 sizeX,uint32 sizeY,bool isFullScreen,EPixelFormat preferredPixelFormat);
    ~VulkanViewport();
    
    Texture2DRHIRef GetBackBuffer(RHICommandListImmediate &rhicmdList);
    void AdvanceBackBufferFrame(RHICommandLisatImmediate & rhiCmdList);
private:
    uint32 index;
};