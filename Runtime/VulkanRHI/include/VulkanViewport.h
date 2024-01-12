#pragma once
#include <RHIViewport.h>
#include "VulkanMemory.h"
#include <Vector2.hpp>
class VulkanViewport:public RHIViewport,public VulkanRHI::DeviceChild
{
public:
    enum{ NUM_BUFFERS=3};

    VulkanViewport(VulkanDevice *device,void *windowHandle,uint32 sizeX,uint32 sizeY,bool isFullScreen,EPixelFormat preferredPixelFormat);
    ~VulkanViewport();
    
    Texture2DRHIRef GetBackBuffer(RHICommandListImmediate &rhicmdList);
    void AdvanceBackBufferFrame(RHICommandLisatImmediate & rhiCmdList);

    virtual void WaitForFrameEventCompletion();
    virtual void IssueFrameEvent();
    virtual Vector2 GetSizeXY(){
        return {sizeX,sizeY}; 
    }
    virtual void SetCustomPresent(RHICustomPresent *customPresent);
    virtual void RHICustomPresent()const override final{
        return customPresent;
    }
    virtual void Tick(float deltaTime)override final;
    bool Present(VulkanCommandListContext*context,VulkanCmdBuffer*cmdBuffert,VulkanQueue *queue,vulkanQueue*presentQueue,bool lockToVsync);
    inline uint32 GetPresentCount()const{
        return presentCount;
    }
    inline bool IsFullScreen()const{
        return isFullScreen;
    }

    inline VkImage GetBackBufferImage(uint32 index){
        if(backBufferImages.num()>0){
            return backBufferImages[index];
        }
        else{
            return VK_NULL_HANDLE;
        }
    }

    inline VulkanSwapChain*GetSwapChain(){

    }

    VkSurfaceTransformFlagBtsKHR GetSwapchainQCOMRenderPassTransform()const;
    VkFormat GetSwapchainImageFormat()const;
protected:
    Array<VkImage>backBufferImage;
    Array<VulkanRHI::Semaphore>RenderingBoneSemaphores;
    Array<VulkanView>textureViews;
    RefCountPtr<VulkanBackBuffer>rhiBackBuffer;
    
private:
    uint32 index;
};