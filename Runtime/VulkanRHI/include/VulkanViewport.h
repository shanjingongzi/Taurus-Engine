#pragma once
#include <RHIViewport.h>
#include "VulkanMemory.h"
class VulkanViewport:public RHIViewport,public VulkanRHI::DeviceChild
{
public:

private:
    uint32 index;
};