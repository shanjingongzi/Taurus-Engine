#pragma once

#include <vulkan/vulkan.h>
#include <Platform.h>
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
    class enum EState:uint8{
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
    VulkanCommandBuffer(VulkanDevice *device,VulkanCommandBufferPool*commandBufferPoos,bool isUploadOnly);
    ~VulkanCommandBuffer();
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
        return state==EState::Submiited;
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

    void BeginRenderPass();
    void EndRenderPass();

};

class VulkanCommandBufferPool
{

};

class VulkanCommandBufferManager
{

};