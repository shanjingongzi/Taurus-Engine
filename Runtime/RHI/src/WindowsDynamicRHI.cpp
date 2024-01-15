#include "RHIDefinitions.h"

static IDynamicRHIModule *LoadDynamicRHIModule(ERHIFeatureLevel::Type &desiredFeatureLevel,const char *loadRHIModuleName)
{

}
const char *GetSelecteddynamicRHIModuleName(bool cleanup)
{
    check(App::CanEverRender());
    ERHIFeatureLevel::Type desiredFeatureLevel;
    const char *rhiModuleName;
    IDynamicRHIModule *dynamicRHIModule=LoadNamicRHIModule(desiredFeatureLevel,rhiModuleName);
    if(dynamicRHIModule &&dynamicRHIModule->IsSupported()){

    }

}