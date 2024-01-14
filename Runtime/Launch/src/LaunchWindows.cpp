#include <Windows.h>

#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)
#define LAUNCH_API DLLEXPORT

extern int32 GuardedMain(const char *cmdLine);

LAUNCH_API int32 LaunchWindowsStartup(HINSTANCE hInstance,HINSTANCE hPrevInstance,char *,int32 nCmdshow,const char *cmdLine)
{
    ErrorLevel=GuardedMain(cmdLine);
}


LAUNCH_API void LaunchWindowShutDown()
{
    EngineLoop::AppExit();
}

int32 WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE prevInstance,_In_ char * cmdLine,_In_ int32 cmdShow)
{
    int32 Result=LaunchWindowsStartup(hInstance,hPrevInstance,cmdLine,cmdShow,nullptr);
    LaunchWindowsShutdown();
    return result;
}