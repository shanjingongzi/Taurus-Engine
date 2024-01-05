#pragma once
#include <Type.hpp>
#include "RHI.h"
#include "RHIDefinitions.h"
#include "RHICommandListImmediate.h"
class RHIResource
{
public:  
    RHIResource(ERHIResourceType resourceType);
    virtual ~RHIResource();
    uint32 AddRef()const;
private:
    void Destroy()const;

public:
    uint32 Release()const;

    uint32 GetRefCount()const;

    static int32 FlushPendingDeletes(RHICommandListImmediate & RHICmdList);

    static bool Bypass();

    bool IsValid()const;

    void Delete();

    void DisableLifeimeExtension();

    ERHIResourceType GetType()const;

    Name GetOwnerName()const;

    void SetOwnerName(const Name &OwnerName);

    virtual bool GetResourceInfo(RHIResourceInfo&outResourceInfo)const;

    static void  BeginTrackingResource(RHIResource *resource);
    static void EndTrackingResource(RHIResource *resource);

    static void StartTrackingAllResource();
    static void StopTrackingAllResource();

private:
    const ERHIResourceType resourceType;
    uint8 committed:1;
    uint8 allowExtentLifeTime:1;
    uint8 beingTracked:1;
    Name ownerName;
    static RHIResource*currentlyDeleting;
    friend class RHICommandListImmediate;
};

class RHICustomPresent:public RHIResource
{
public:
    RHICustomPresent():RHIResource(RRT_CustomPresent){}

    virtual ~RHICustomPresent(){}

    virtual void OnBackBufferSize()=0;

    virtual bool NeedNativePresent()=0;

    virtual bool NeedsAdvanceBackbuffer(){return false;}
    
    virtual void BeginDrawing(){}

    virtual bool Present(int32 &outSyncInterval)=0;

    virtual void PosetPresent(){};

    virtual void OnAquireThreadOwnership(){}

    virtual void OnReleaseThreadOwnership(){}
};

class RHIViewableResource:public RHIResource
{
public:
    void SetTrackedAccess_Unsage(ERHIAccess access);
    Name GetName()const{
        return name;
    }

protected:
    RHIViewableResource(ERHIResourceType resourceType,ERHIAccess access):RHIResource(resourceType),trackedAccess(access){}
    void TakeOwnership(RHIViewableResource &other){
        trackedAccess=other.trackedAccess;
    }
    void ReleaseOwnership(){
        trackedAccess=ERHIAccess::Unknown;
    }

    Name name;
private:
    ERHIAccess trackedAccess;
    friend class RHIComputeCommandList;
    friend class RHIComputeContext;
};