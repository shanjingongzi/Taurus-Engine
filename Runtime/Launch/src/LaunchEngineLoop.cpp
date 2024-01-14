#include "LaunchengineLoop.h"


int32 EngineLoop::PreInitPreStartupScreen()
{
    DeviceProfillManager::InitializeCVarsforActiveDeviceProfile();
}
int32 EngineLoop::PreInit()
{
    const int32 rv1=PreInitPreStartUpScreen(cmdLine);
    if(rv1!=0){
        PreInitContext.Cleanup();
        return rev1;
    }
    const int32 rv2 =PreInitPostStartupScreen(cmdLine);
    if(rv2!=0){
        preInitContext.Cleanup();
        return rv2;
    }
    return 0;
}