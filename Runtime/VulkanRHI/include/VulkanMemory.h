#pragma once
#include <ThreadSafeCounter.h>
#include <AssertionMacros.h>
class VulkanDevice;

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

namespace VulkanRHI
{
    class RefCount
    {
    public:
        RefCount(){}
        virtual ~RefCount(){
            check(numRefs.GetValue()==0);
        }
        inline uint32 AddRef(){
            int32 newValue=numRefs.Increament();
            check(newValue>0);
            return (uint32)newValue;
        }
        inline uint32 Release(){
            int32 newValue=numRefs.Decrement();
            if(newValue==0){
                delete this;
            }
            check(newValue>=0);
            return (uint32)newValue;
        }
        inline int32 GetRefCounter()const{
            int value=numRefs.GetValue();
            check(value>0)
            return (uint32)value;
        }
    private:
        ThreadSafeCounter numRefs;
    };

    class DeviceChild
    {
    public:
        DeviceChild(VulkanDevice *device):device{device}
        {
        }
        class VulkanDevice*GetParent()const{
            return device;
        }

    protected:
        VulkanDevice*const device;
    };
}