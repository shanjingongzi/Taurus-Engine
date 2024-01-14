#include <RHI.h>
#include <VulkanLoader.h>

class VulkanGenericPlatform
{
public:
    static bool IsSupported(){return true;}

    static bool LoadVulkanLibray(){return true;}
    static bool LoadVulkanInstanceFunctions(VkInstance instance);
    static void ClearVulkanInstanceFuncions();
    static void FreeVulkanLibrary();

    static void InitDevice(VulkanDeivce *device); 
}