#pragma once

namespace
{
    class DeviceChild
    {
    public:
        DeviceChild();
        RHIVulkanDevice*GetParent()const{
            return device;
        }

    protected:

    }
}