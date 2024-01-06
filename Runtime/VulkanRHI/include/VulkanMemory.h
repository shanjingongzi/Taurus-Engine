#pragma once

namespace VulkanRHI
{
    class FenceManager;
    class DevicememoryManager;
    class DeviceMemoryAllocation;
    class VulkanSubresourceAllocator;
    class MemoryManager;
    class Range;
    class VulkanAllocation;
    class VulkanAllocationInternal;
    class ResourceHeapStates;
};

namespace
{
    class DeviceChild
    {
    public:
        DeviceChild();
        VulkanDevice*GetParent()const{
            return device;
        }

    protected:

    }
}