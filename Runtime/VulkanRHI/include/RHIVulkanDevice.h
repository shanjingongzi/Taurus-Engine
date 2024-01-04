#pragma once
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
    }
}