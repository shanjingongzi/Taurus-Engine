#pragma once
#include <map>
#include <vulkan/vulkan.h>
#include <Array.hpp>
class VulkanDevice;
class VulkanCommandBufferPool;
class VulkanCommandBuffermanager;
class VulkanRenderTargetLayout;
class VulkanQueue;
class VulkanDescriptorPoolSetContainer;
class VulkanGPUTiming;

class VulkanCmdBuffer
{
public:
    enum class EState:uint8{
        ReadyForBegin,
        IsInsideBegin,
        IsInsideRenderPass,
        HasEnded,
        Submitted,
        NotAllocated,
        NeedReset
    };
protected:
    friend class VulkanCommandBufferManager;
    friend class VulkanCommandBufferPool;
    friend class VulkanQueue;
protected:
    VulkanCmdBuffer(VulkanDevice *device,VulkanCommandBufferPool*commandBufferPoos,bool isUploadOnly);
    ~VulkanCmdBuffer();
public:
    VulkanCommandBufferPool *GetOwner(){
        return commandBufferPool;
    }

    VulkanDevice*GetDevice(){
        return device;
    }
    bool IsUniformBufferBarrierAdded()const{

    }

    inline bool IsInsideRederPass()const{
        return state==EState::IsInsideRenderPass;
    }
    inline bool IsOutsideRenderPass()const{
        return state==EState::IsOutsideRenderPass;
    }
    inline bool hasBegun()const{
        return state==EState::IsInsideBegin||state==EState::IsInsideRenderPass;
    }
    inline bool HasEnded(){
        return state==EState::HasEnded;
    }
    inline bool IsSubmitted()const{
        return state==EState::Submitted;
    }
    inline bool IsAllocated()const{
        return state!=EState::NotAllocated;
    }
    inline VkCommandBuffer GetHandle(){
        return commandBufferHandle;
    }
    inline volatile uint64 GetFenceSignaledCounter()const{
        return fenceSignaledCounter;
    }
    inline volatile uint64 GetSubmittedFenceCounter()const{
        return sumbittedFenceCounter;
    }
    inline VulkanLayoutManger &GetLayoutManager(){
        return layoutManager;
    }
    inline bool HasValidTiming()const{
        return (timing !=nullptr) &&(std::abs((int64)fenceSignaledCounter-(int64)lastvalidTiming)<3);
    }
    void AddWaitSemaphore(VkPipelineStageFlags waitFlags,VulkanRHI::Sempaphore*inWaitSemaphore){
    }
    void AddWaitSemaphore(VkPipelinestageFlags waitFlags,Array<VulkanRHI::Semaphore*>waitSemaphores);
    void Begin();
    void End();

    Array<VkViewport>currentViewports;
    Array<VkRect2D>currentScissors;
    uint32 currentStencilRef;
    EState state;
    uint8 needsDynnnnamicsStateSet:1;
    uint8 hasPipeline:1;
    uint8 hasViewport:1;
    uint8 hasScissor:1;
    uint8 hasStencilRef:1;
    uint8 isUploadOnly:1;
    uint8 isUnformBufferBarrierAdded:1;

    void BeginRenderPass(const VulkanRenderTargetLayout &layout,class VulkanRenderPass*renderPass,class VulkanFrameBuffer *frameBuffer,const VkClearValue*attachmentClearValue);
    void EndRenderPass();

    void BeginUniformUpdateBarrier();
    void EndUniformUpdatebarrier();

    VulkanDescriptorPoolSetContainer*currentDescriptorPoolSetContainter=nullptr;
 
    bool AcquirePoolSetAndDescriptorIfNeeded(const class VulkanDescriptorSetLayout&layout,bool needDescriptors,VkDescriptorSet *outDescripotrSet);

    struct PendingQuery{
        uint64 index;
        uint64 count;
        VkBuffer bufferHandle;
        VkQueryPool poolHandle;
        bool blocking;
    };
    void AddPendingTimestampQuery(uint64 index,uint64 count,VkQueryPool poolHandle,VkBuffer bufferHandle,bool blocking);
private:
    VulkanDevice *device;
    VkCommandBuffer commandBufferHandle;
    double submittedtime=0.0f;
    Array<VkPipelineStageFlags>waitFlags;
    Array<VulkanRHI::Semaphore*>waitSemaphore;
    Array<VulkanRHI::Semaphore*>submittedWaitSemaphores;
    Array<PendingQuery>pendingTimestampQueries;

    void MarkSeamphoreAsSubmiited(){
        waitFlags.clear();
        submittedWaitSemaphores=waitSemaphore;
        waitSemaphore.clear();
    }

    VulkanRHI::Fence *fence;
    volatile uint64 fencesignaledCounter;
    volatile uint64 submittedFenceCounter;
    void RefreshfenceStatus();
    void Initializetimings(class VulkanCommandListContext *context);
    VulkanCommandBufferPool *commandBufferPool;
    class VulkanGUITiming *timing;
    uint64 lastvalidTiming;
    void AcquirePoolSetContainer();
    void AllocMemory();
    void FreeMemory();
    VulkanLayoutManager layoutManager;
public:
    std::map<uint32,class vulkantypeDescriptorPoolSet*>typeDescriptorPoolSets;
    friend class VulkanDynamicRHI;
    friend class VulkanLayoutManager;

};

class VulkanCommandBufferPool
{
public:
    VulkanCommandBufferPool(VulkanDevice *device,VulkanCommandBuffermanager&inMgr);
    ~VulkanCommandBufferPool();
    void RefreshFenceStatus(VulkanCmdBuffer skipcmdBuffer*=nullptr);
    inline VkCommandPool GetHandle(){
        return handle;
    }
    inline CritileSetion*GetCs(){
        return &cs;
    }
    void FreeUnusedCmdBuffer(VulkanQueue *queue);
    inline VulkanCommandBufferManager &GetMrg(){
        return mgr;
    }
private:
    VkCommandBuffer handle;
    Array<VulkanCmdBuffer*>cmdBuffers;
    Array<VulkanCmdBuffer*>freeCmdBuffers;
    CriticalSetion cs;
    VulkanDevice *device;
    VulkanCommandBufferManager  &mgr;
    
    VulkanCmdBuffer*Create(bool isUploadOnly);
    void Create(uint32 QueueFamilyIndex);
    friend class VulkanCommandBufferManager;
};

class VulkanCommandBufferManager
{
public:
    VulkanCommandBufferManager(VulkanDevice *device,class VulkanCommandListContext*context);
    ~VulkanCommandBufferManager();
    void Init(VulkanCommandListContext *context);
    inline VulkanCmdBuffer *GetActiveCmdBuffer(){
        if(uploadCmdBuffer){
            submitUploadCmdBuffer();
        }
        return activeCmdBuffer;
    }

    inline VulkanCmdBuffer *GetActiveCmdBufferDirect(){
        return activeCmdBuffer;
    }

    inline bool HasPendingUplaodCmdBuffer()const{
        return uploadCmdBuffer!=nullptr;
    }

    inline bool HadPendingActiveCmdBuffer()const{
        return activeCmdBuffer!=nulptr;
    }

    VulkanCmdBuffer*GetUploadCmdBuffer();

    void SubmitUploadCmdBuffer(uint32 numSignaledSemaphore =0,VkSemaphore *signalSemaphore=nullptr);

    void SubmitActiveCmdBuffer(Array<VulanRHI::Semaphore>sigalSemaphore);
    void SubmitActiveCmdBUffer()
    {
        SubmitActiveCmdBuffer({nullptr,0});
    }
    void SubmitActiveCmdBUffer(VulkanRHI::SignalSemaphore);
    void SubmitActivecmdBufferFromPresent(VulkanRHI::Semaphore *signalSemaphore=nullptr);

    void FlushResetQueryPools();

    void RefreshFenceStatus(VulkanCmdBuffer *skeipCmdBuffer=nullptr){
        pool.RefreshFfenceState(skipCmdBurrer);
    }

    void PrepareFornewActiveCommandBuffer();

    inline VkCommandPool GetHandle()const{
        return pool.GetHandle();
    }

    uint32 CalculateGPUTime();
    inline VulkanCommandListContext *GetCommandListContext(){
        return context;
    }

    inline VulkanQueue *GetQueue(){
        return queue;
    }

    inline void NotifyDeletedImage(VkImage image){
        if(uploadCmdBuffer){
            return uploadCmdBuffer->GetLayoutManager().NotifyDeletedImage(image);
        }
        if(activeCmdBuffer){
            return activeCmdBuffer->GetLayoutManager().NotifyDeletedImage();
        }
    }
private:
    struct QueryPoolReset{
        VkQueryPool pool;
        uint32 size;
    };
    VulkanDevice *device;
    VulkanCommandListContext *context;
    VulkanCommandBufferPool pool;
    VulkanQueue *queue;
    VulkanCmdBuffer*activeCmdBuffer;
    VulkanCmdBuffer*uploadcmdBuffer;
    Array<QueryPoolReset>poolResets;
    VulkanRHI::Semaphore activeCmdBufferSemaphore;
    Array<VulkanRHI::Semaphore*>renderingCompletedSemaphore;
    VulkanRHI::Semaphore*uploadCmdBufferSemaphore;
    Array<VulkanRHI::Semaphore *>uploadCompletedSemahphores;
};