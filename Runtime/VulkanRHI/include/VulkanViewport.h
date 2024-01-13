#pragma once
#include <RHIViewport.h>
#include "VulkanMemory.h"
#include <Vector2.hpp>

namespace VulkanRHI
{
    class Semaphore;
};
class VulkanBackBuffer:public VulkanTextrue
{
public:
    VulkanBackBuffer(VulkanDevice  &device,VulkanViewport *viewport,EPixelFormat format,uint32 sizeX,uint32 sizeY,ETextureCreateFlags flags);
    virtual ~VulkanBackBuffer();
    
    void OnLayoutTransition(VulkanCommandListContext &context,VkImageLayout newLayout)override final;
    void OnGetBackBufferImage(RHICommandListImmediate&rhicmdList);
    void OnAdvanceBackBufferFrame(RHICommandListImmediate &rhiCmdList);
private:
    void AcquirebackBufferImage(VulkanCommandListContext &context);
private:
    VulkanViewport *viewport;
};

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
    RefCountPtr<VulkanTexture>renderingBackBuffer;
    CriticalSection recreatingSwapchain;

    uint32 sizeX;
    uint32 sizeY;
    bool isFullScreen;
    EPixelFormat pixelFormat;
    int32 acquiredSemaphore;
    CustomPresentRHIRef customPresent;
    VulkanCmdBuffer *lastFrameCommandBuffer=nullptr;
    uint64 lastFrameFenceCounter;
    void CreateSwapchain(struct VulkanSwapChainRecreateInfo *recreateInfo);
    void DestroySwapChain(struct VulkanSwapChainRecreateInfo *recreateInfo);
    bool TruAcquireImageIndex();

    void RecreateSwapchain(void *newNativeWindow);
    void RecreateSwapchainFromRT(struct EPixelFormat preferredPixelFormat);
    void Resize(uint32 sizeX,sizeY,bool isFullScreen,EPixelFormat preferredPixelFormat);

    bool DoCheckedSwapChainJob(std::function<int32(VulkanViewport*)>swapChainJob);
    bool SupportsStandardSwapchain();
    bool RequiesRenderingbackBuffer();
    EPixelFormat GetPixelFormatForNonDefaultSwapchain();

    friend class VulkanDynamicRHI;
    friend class VulkanCommandListContext;
    friend class RHICommandAcquireBackBuffer;
    friend class VulkanBackBuffer;
};

template<>
struct VulkanResourceTraits<RHIViewport>
{

};