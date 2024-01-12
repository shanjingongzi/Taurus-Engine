#pragma once
#include <Array.hpp>
#include <vulkan/vulkan.h>
#include <RHIDefinitions.h>
namespace
{
    class RHIVulkanDevice
    {
    public:
        RHIVulkanDevice(class VulkanDynamicRHI*rhi,VkPhysicalDevice gpu);
        ~RHIVulkanDevice();
        void InitGPU();
        void CreateDevice();
        void PrepareForDestroy();
        void Destroy();
        void WaitUntilIdle();
        inline EGpuVendorId GetVendorId()const;
        inline bool HasAsyncComputeQueue()const;
        inline bool CanPresentOnComputeQueue()const;
        inline bool IsRealAsyncComputeContext(const VulkancommandListContext *context)const;
        inline VulkanQueue*GetGraphicsQueue();
        inline VulkanQueue*GetComputeQueue();
        inline VulkanQueue*GetTransferQueue();
        inline VulkanQueue*GetPresentQueue();
        inline VkPhysicalDevice GetPhysicalHandle()const;
        inline const VkPhysicalDeviceProperties&GetDeviceProperties()const;
        inline VkExtent2D GetBastMatchedFragmentSize();
    private:
        VkDevice device;
        VulkanRHI::DeviceMemoryManager deviceMemoryManager;
        VulkanRHI::Memorymanager memroyManager;
        VulkanRHI::DeferredDeletionQueue2 deferredDeletionQueue;
        VulkanRHI::StagingManager stagingManager;
        VulkanRHI::FenceManager fenceManager;
        VulkanRenderPassmanager renderPassManager;
        VulkanTransientHeapCache *transientheapCache;
        VulkanDescriptorSetCache*descriptorSetCache;
        VulkanDescriptorPoolsManager *descriptorPoolsManager;
        VulkanBindlessDescriptorManager *bindlessDescriptorManager;
        VulkanShaderFactory shaderFactory;
        VulkanSmplerState*defaultSampler;
        VulkanTexture*defaultTexture;
        VkPhysicalDevice gpu;
        VkPhysicalDeviceProperties gpuProps;
        VulkanPhysicalDeviceFeatures physicalFeatures;
        Array<VkPhysicalDeviceFragmentShadingRateKHR>framentShaderingRates;
    };
}