#pragma once
#include <string>
#include <IModuleInterface.h>
class IDeviceProfileSelectorModule:public IModuleInterface
{
public:
    virtual std::string GetRuntimeDeviceProfileName(){
        return {};
    }
};