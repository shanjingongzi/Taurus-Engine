#include "VulkanDynamicRHIModule.h"
#include "VulkanWindowsPlatform.h"
bool VulkanDynamicRHIModule::IsSupported(){
    if(VulkanPlatform::IsSuppored()){
        return VulkanPlatform::LoadVulkanLibray();
    }
    return false;
}

bool VulkanDynamicRHIModule::IsSupported(){
    
}