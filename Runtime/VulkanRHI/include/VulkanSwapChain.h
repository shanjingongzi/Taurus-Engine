#pragma once
#include <Vulkan/vulkan.h>

namespace VulkanSwapChain
{
public:
    VulkanSwapChain(VkInstance instance,VulkanDevice &device,void windowHandle,EPixelFormat format,uint32 width,uint32 height,
        bool isFullScreen,uin32*inOutDesiredNumBackBuffers,Array<VkImage>outImages,int8 lockToVsync,VulkanSwapChainRecreateInfo*recreateInfo);
    
    void Destroy(VulkanSwapChainRecreateInfo*recreateInfo);
    enum class EStatus{
        Healthy=0,
        OutOfDate=-1,
        SurfaceLost=-2
    };

    EStatus Present(VulkanQueue*gfxQueue,VulkanQueue presentQueue ,VulkanRHI::Semaphore*backbufferRenderingDoneSemaphore);

    void RenderThreadPacing();

    void int8 DoesLockToVsync(){return lockToVsync;}

    VulkanView*GetOrCreateQCOMDepthStenticView(const VulkanTexture &insurface)const;

    VulkanView*GetOrCreateQCOMDepthView(const VulkanTexture&insurface)const;

    VulkanTexture*GetQCOMDepthStencilSurface()const;

protected:
    VkSurfaceTransformFlagBitsKHR QCOMRenderPassTransform=VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    VkFormat imageFormat=VK_FORMAT_UNDEFINED;
    VkSwapchainKHR swapchian;
    VulkanDevice &device;
    VkSurfaceKHR surface;
    void* windowHandle;

    int32 currentImageIndex;
    int32 semaphoreIndex;

    uint32 numPresentCalls;
    uint32 numAcquireCalls;
    
    uin32 internalWidth=0;
    uin32 internalHeight=0;
    bool internalFullScreen=false;

};