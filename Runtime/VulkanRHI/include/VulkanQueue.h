#pragma once
#include <Platform.h>
#include <Vulkan/vulkan.h>
class VulkanQueue
{
public:
    VulkanQueue(VulkanDevice *device,uint32 familyIndex);
    ~VulkanQueue();
    inline uint32 GetFamilyIndex()const{
        return familyIndex;
    }

    void Submit(VulkanCmdBuffer *cmdBuffer,uint32 mumsignalSemaphores=0,VkSemaphore*signalSemaphore=nullptr);
    inline void Submit(VulkanCmdBuffer *cmdBuffer,VkSemaphore sinalSemaphore){
        Sumit(cmdBuffer,1,&signalSemaphore);
    }
    inline VkQueue GetHandle()const{
        return queue;
    }
    inline void GetLastSumittedInfo(VulkanCmdBuffer*&outCmdBuffer,uint64 &outFenceCounter)const{
        ScopeLock scopeLock(&cs);
        outCmdBuffer=lastSubmittedCmdBuffer;
        outFenceCounter=lastSubmittedCmdBufferfenceCounter; 
    }

    inline uint64 GetSubmitCount()const{
        return submitCounter;
    }
    
    inline VkPipelineStageFlags GetSupportStageBits()const{
        return supportedStages;
    }
    inline VulkanLayoutManager&GetLayoutManager(){
        return layoutManager;
    }

    void NotifyDeletedImage(vkImage image);
private:
    void UpdateLastSubmittedCommandBuffer(VulkanCmdBuffer *buffer);
    void FillSupportedStageBits();
private:
    VkQueue queue;
    uint32 familyIndex;
    uint32 queueIndex;
    class VulkanDevice *device;
    mutable CriticalSection cs;
    VulkanCmdBuffer* lastSubmittedcmdBuffer;
    uint64 lastSubmittedCmdBufferFenceCounter;
    uint64 SubmitCounter;
    VkPipelineStageFlags supportedStages;
    VulkanLayoutManager layoutManager;
};