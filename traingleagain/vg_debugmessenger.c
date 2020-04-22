#include "vg_setup.h"

#include <assert.h>

#ifdef DEBUG
#include <stdio.h>
#endif // DEBUG

//debug messenger info
#define MESSAGE_SEVERITY VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
#define MESSAGE_TYPE VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT


//DEBUG MESSENGER 
static VKAPI_ATTR VkBool32 VKAPI_CALL vgSet_debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{
#ifdef DEBUG
	printf("\n\nValidation Layer: %s", pCallbackData->pMessage);
#endif // DEBUG	
	return VK_FALSE;  //typically we just return false unless we are testing the validation layers themselves, which i am in no way qualified to do
}

VkDebugUtilsMessengerCreateInfoEXT vgSet_DebugMessengerInfo()
{
	VkDebugUtilsMessengerCreateInfoEXT DebugMessenger =
	{
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
		.pNext = NULL,
		.flags = 0,  //this one is zero according the docs, it is NULL for most of the other structure that I've filled out so far
		.messageSeverity = MESSAGE_SEVERITY,  //bitmask of VkDebugUtilsMessageSeverityFlagBitsEXT which severity will trigger?
		.messageType = MESSAGE_TYPE, //bitmask of VkDebugUtilsMessageTypeFlagBitsEXT which types will trigger?
		.pfnUserCallback = vgSet_debugCallback,  //dat function
		.pUserData = NULL //optional
	};
	//this structure should be passed to the vkCreateDebugUtilsMessengerEXT function to create the VkDebugUtilsMessengerEXT object
	//this function is an extension function so it is not automatically loaded :(
	//that is why we have to call the vkGetInstanceProcAddr thing
	return DebugMessenger;
}

VkResult vgSet_DebugUtilsMessengerEXT(VkInstance hInstance,
	const VkDebugUtilsMessengerCreateInfoEXT* pDebugMessengerInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	//our goal here is to load the vkCreateDebugUtilsMessengerEXT
	PFN_vkCreateDebugUtilsMessengerEXT Function = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(hInstance, "vkCreateDebugUtilsMessengerEXT");

	if (Function == NULL)
	{
#ifdef DEBUG
		printf("\nWe failed to load the extension!!!  aaaahhhhh!!!!");
#endif // DEBUG
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
	else
		return Function(hInstance, pDebugMessengerInfo, pAllocator, pDebugMessenger);
}


//CREATE DESTROY
VkDebugUtilsMessengerEXT vgCreate_DebugMessenger(VkInstance hInstance, const VkAllocationCallbacks* pAllocator)
{
	//oh shit here we go
	VkDebugUtilsMessengerCreateInfoEXT DebugMessengerInfo = vgSet_DebugMessengerInfo();
	VkDebugUtilsMessengerEXT DebugMessenger;
	VkResult rezzy = vgSet_DebugUtilsMessengerEXT(hInstance, &DebugMessengerInfo, pAllocator, &DebugMessenger);
	assert(rezzy == VK_SUCCESS);
	return DebugMessenger;
}
void vgDestroy_DebugMessenger(VkInstance hInstance, VkDebugUtilsMessengerEXT DebugMessenger, const VkAllocationCallbacks* pAllocator)
{
	PFN_vkDestroyDebugUtilsMessengerEXT Function = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(hInstance, "vkDestroyDebugUtilsMessengerEXT");
	if (Function != NULL)
		Function(hInstance, DebugMessenger, pAllocator);
}
