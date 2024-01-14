#pragma once

class EngineLoop:public IEngineLoop
{
public:
    EngineLoop();
    virtual EngineLoop();
public:
    int32 PreInit(int32 argc,char *argv[],const char *additionalCommandLine=nullptr);

    int PreInit(const char*cmdLine);

    int32 PreInitPreStartupScreen(const char *cmdLine);

    int32 PreInitPostStartScrenn(const char *cmdLine);    

    void LoadPreInitModules();

    bool LoadcoreModule();

    void clearnupPreInitContext();
};