#pragma once




class VulkanDynamicRHIModule:public IDynamicRHIModule
{
public:
    virtual StartupModule()override;
    virtual bool IsSupported()override;
    virutal bool IsSupported(ERHIFeatrueLevel::Type requestedFeatureLevel)override;
    virtual DynamicRHI*CreateRHI(ERHIFeatrueLevel::Type requestedFeatrueLevel=ERHIFeatrueLevel::Num)override;
}