#pragma once

class IModuleInterface
{
public:
    virtual ~IModuleInterface(){}

    virtual void StartupModule(){
    }

    virtual void PreUnloadCallback(){

    }

    virtual void PostLoadCallback(){

    }

    virtual void ShutdownModule(){

    }

    virtual bool SupportdynamicReloading(){
        return true;
    }

    virtual bool SupportsAutomaticshutdown(){
        return true;
    }

    virtual bool IsGameModule()const{
        return false;
    }
};