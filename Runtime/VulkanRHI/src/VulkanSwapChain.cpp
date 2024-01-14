#include "VulkanSwapChain.h"

VulkanSwapChain::VulkanSwapChain()
{
    if(recreateInfo!=nullptr &&recreteInfo->swapChain!=VK_NULL_HANDLE){
        check(recreateInfo->surface !=VK_NULL_HANDLE);
        surface=recreateInfo->surface;
        recreateInfo->surface=VK_NULL_HANDLE;
    }
    else{
        VulkanPlaform::CreateSurface(windowHandle,instance,&surface);
    }
}

VulkanSwapChain::~VulkanSwapChain()
{

}

