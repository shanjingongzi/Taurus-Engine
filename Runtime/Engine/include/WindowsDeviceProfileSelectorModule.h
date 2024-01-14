#pragma once
#include <string>
#include "IDeviceProfileSelectorModule.h"
class WindowDeviceProfileSelectorModule:public IDeviceProfileSelectorModule
{
public:
    const std::string GetRuntimeDeviceProfileName()override; 
}