#include "VulkanViewport.h" 

void VulkanViewport::CreateSwapchain(VulkanSwapChainRecreateInfo *recreateInfo)
{
    renderingBackBuffer=nullptr;
    rhiBackBuffer=nullptr;
    if(SupportsStandardSwapchain()){
        uint32 desiredUnmBackBuffers=NUM_BUFFERS;
        Array<VkImage>images;
        swapChain=new VulkanswapChain(VulkanDynamicRHI::Get().instance,*device,windowHandle,pixelFormat,sizeX,sizeY,isFullScreen,
            &desireNumBackBuffers,Images,lockToVsync,recreateInfo
        );
        
    }

}