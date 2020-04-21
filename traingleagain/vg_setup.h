#ifndef _VG_SETUP_H_
#define _VG_SETUP_H_

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif // !GLFW_INCLUDE_VULKAN

//GLFW WINDOW
GLFWwindow* init_create_GLFWwindow();
void destroy_terminate_GLFWwindow(GLFWwindow* pMyWindow);

static _inline const char** get_GLFWExtension(uint32_t* pn_RequiredEXTs)
{
	return glfwGetRequiredInstanceExtensions(pn_RequiredEXTs);
}

//DEBUG MESSENGER
VkDebugUtilsMessengerEXT create_DebugMessenger(VkInstance hInstance, const VkAllocationCallbacks* pAllocator);
void destroy_DebugMessenger(VkInstance hInstance, VkDebugUtilsMessengerEXT DebugMessenger, const VkAllocationCallbacks* pAllocator);

VkDebugUtilsMessengerCreateInfoEXT fill_DebugMessengerInfo();

//DEVICE USAGE TRACKER

//going to use SoA for this.  If not required tis good practice.  right?
struct VgDeviceQueueFamiliesUsage
{
	//capabilities:
	uint32_t N_QueueFamilies;
	VkQueueFlags* QueueFlags;  //use this and the reference below to check capabilities when assigning queues
	uint32_t* pMaxQ;
	//in use:
	uint32_t* pN_Graphics;
	uint32_t* pN_Compute;
	uint32_t* pN_Transfer;
	uint32_t* pN_Sparse;
	uint32_t* pN_Protected;

	//for reference when checking for capabilities
	//typedef enum VkQueueFlagBits {
	//	VK_QUEUE_GRAPHICS_BIT = 0x00000001,
	//	VK_QUEUE_COMPUTE_BIT = 0x00000002,
	//	VK_QUEUE_TRANSFER_BIT = 0x00000004,
	//	VK_QUEUE_SPARSE_BINDING_BIT = 0x00000008,
	//	VK_QUEUE_PROTECTED_BIT = 0x00000010,
	//	VK_QUEUE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
	//} VkQueueFlagBits;
};
typedef struct VgDeviceQueueFamiliesUsage* hVgDeviceQueueFamiliesUsage;

//this is to track usage.  Hopefully I will remember to require all functions that create queues to require this struct
//don't think I need to take the address of the device because it is already a handle
hVgDeviceQueueFamiliesUsage create_DeviceUsageTracker(VkPhysicalDevice hDevice);
void destroy_DeviceUsageTracker(hVgDeviceQueueFamiliesUsage hDeviceUsage);

#endif // !_VG_SETUP_H_

