#include "WindowsDeviceProfileSelectorModule.h"

const std::string WindowsDeviceProfileSelectorModule::GetRuntimeDeviceProfileName()
{
    std::string profileName=PlatformProperties::Platformname();
    auto profilename=GetSelectedDynamicRHIModuleName(false);
    return profilename;
}