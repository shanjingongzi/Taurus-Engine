#pragma once
#include <Array.hpp>
namespace
{
    class RHIVulkanDevice
    {
    public:
        RHIVulkanDevice(class VulkanDynamicRHI*rhi,VkPhsicalDevice gpu);
        ~RHIVulkanDevice();
        void InitGPU();
        void CreateDevice();
        void PrepareForDestroy();
        void Destroy();
        void WaitUntilIdle();
        inline EGPUVendoeId GetVendorId()const;
        inline bool HasAsyncComputeQueue()const;
        inline bool CanPresentOnComputeQueue()const;
        inline bool IsRealAsyncComputeContext(const VulkancommandListContext *context)const;
        inline RHIVulkanQueue*GetGraphicsQueue();
        inline RHIVulkanQueue*GetComputeQueue();
        inline RHIVulkanQueue*GetTransferQueue();
        inline RHIVulkanQueue*GetPresentQueue();
        inline VulkanPhysicalDevice GetPhysicalHandle()const;
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
};