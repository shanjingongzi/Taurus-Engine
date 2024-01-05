#include "VulkanQueue.h"

VulkanQueue::VulkanQueue(VulkanDevice *InDevice,uint32 inFamilyIndex):queue{VK_NULL_HANDLE},familyIndex{inFamilyIndex},device{InDevice},queueIndex{0},
    lastSubmittedCmdBuffer(nullptr),lastSubmittedCmdBufferFenceCounter(0),submitCounter(0),layoutManager(false,nullptr)
{

}

VulkanQueue::~VulkanQueue()
{

}

void VulkanQueue::Submit(VulkanCmdBuffer*cmdBuffer,uint32 numSignalSemaphore,VkSemaphore*signalSemaphore)
{
    check(CmdBuffer->HasEnded());
    VulkanRHI::Fence*fence=fence=cmdBuffer->fence;
    check(!fen->IsSignaled());

    const VkCommandBuffer cmdBuffers[]=(cmdBuffer->GetHandle());
    VkSumbitInfo sumbitInfo;
    sumbitInfo.commandBufferCount=1;
    sumbitInfo.pCommandBuffers=cmdBuffers;
    sumbitInfo.sinalSemaphoreCount=numSignalSemaphore;
    sumbitInfo.pSignalsemaphores=vkSignalSemaphore;
}
