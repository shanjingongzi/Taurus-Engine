#pragma once
#include <vulkan/vulkan.h>

class VulkanWindowsPlatform:public VulkanGenericPlatform
{
public:
    static bool LoadVulkanLibray();
    static bool LoadVulkanInstanceFunctions(VkInstance instance);
    static void FreeVulkanLibrary();

    static void GetInstanceExtensions(VulkanInstanceExtensionArray &outExtensions);
    static void GetInstanceLayers(Array<const char*>outLayers);
    static void GetDeviceExtensions(VulkanDevice *device,VulkanDeviceExtensionArray &outExtension);
    static void GetDeviceLayers(Array<char *>&outLayers){}

    static void CreateSurface(void *windowHandle,VkInstance instance,VkSurfaceKHR*outSurface);

    static void SupportsDeviceLocalhostVisibleWintNoPenalty(EGpuVendorId vendorId);
    
    static void WriteCrashMarker(const OptionalVulkanDeviceExtensions &optionalExtension,VkCommandBuffer cmdBuffer,VkBuffer destBuffer,cosnt Array<uint32>&entries,bool adding);
    
    static void WriteCrashMarker(const OptionalVulkanDeviceExtensions &optionalExtension,VkCommandBuffer cmdBuffer,VkBuffer destBuffer,cosnt Array<uint32>&)
}