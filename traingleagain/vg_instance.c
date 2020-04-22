#include "vg_setup.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#include <stdio.h>
#endif // DEBUG

//application info
const char* APPLICATION_NAME = "Hello Triangle";
#define APPLICATION_VERSION VK_MAKE_VERSION(0, 0, 0)
const char* ENGINE_NAME = "No engine";
#define ENGINE_VERSION VK_MAKE_VERSION(0, 0, 0)
#define API_VERSION VK_API_VERSION_1_1

//Instance create Info release
const uint32_t N_ENABLED_LAYERS_RELEASE = 0;
const char** NAMES_ENABLED_LAYERS_RELEASE;

//Instance create info debug
const uint32_t N_ENABLED_LAYERS_DEBUG = 1;
const char* NAMES_ENABLED_LAYERS_DEBUG[] = { "VK_LAYER_KHRONOS_validation" };

typedef enum
{
	MISSING = 0,
	PRESENT = 1
}Presence;

//CHECKS
Presence vgCheck_ValidationLayers()
{
	uint32_t n_VAL = 0;
	VkResult rezzy = vkEnumerateInstanceLayerProperties(&n_VAL, NULL);
	VkLayerProperties* pLayers = (VkLayerProperties * )malloc(sizeof(VkLayerProperties) * n_VAL);
	vkEnumerateInstanceLayerProperties(&n_VAL, pLayers);

	//outloop through requested layers
	Presence AllLayersPresent = PRESENT;
	for (uint32_t i = 0; i < N_ENABLED_LAYERS_DEBUG; i++)
	{
		Presence LayerPresent = MISSING;
		const char* Requested_Layer_i = NAMES_ENABLED_LAYERS_DEBUG[i];
		for (uint32_t j = 0; j < n_VAL; j++)
		{
			char* Available_jth = pLayers[j].layerName;
			if (strcmp(Requested_Layer_i, Available_jth) == 0)
				LayerPresent = PRESENT;
		}
		if (LayerPresent == MISSING)
			AllLayersPresent = MISSING;
	}
	return AllLayersPresent;
}


//INSTANCE STRUCTURES
VkApplicationInfo vgSet_AppInfo()
{
	VkApplicationInfo AppInfo =
	{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = NULL,
		.pApplicationName = APPLICATION_NAME,
		.applicationVersion = APPLICATION_VERSION,
		.pEngineName = ENGINE_NAME,
		.engineVersion = ENGINE_VERSION,
		.apiVersion = API_VERSION
	};
	return AppInfo;
}
VkInstanceCreateInfo vgSet_CreateInfo(VkApplicationInfo* pAppInfo, uint32_t n_BaseRequiredEXTs, const char** names_BaseRequiredExts)
{
	VkInstanceCreateInfo CreateInfo =
	{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = NULL,
		.flags = NULL,
		.pApplicationInfo = pAppInfo,
		.enabledLayerCount = N_ENABLED_LAYERS_RELEASE,
		.ppEnabledLayerNames = NAMES_ENABLED_LAYERS_RELEASE,
		.enabledExtensionCount = n_BaseRequiredEXTs,
		.ppEnabledExtensionNames = names_BaseRequiredExts
	};
	return CreateInfo;
}
void vgSet_Validation(VkInstanceCreateInfo* pCreateInfo)
{
	Presence LayersPresent = vgCheck_ValidationLayers();
#ifdef DEBUG
	if (LayersPresent != PRESENT)
		printf("\nrequested validation layers where not found");
#endif // DEBUG
	assert(LayersPresent == PRESENT);
	pCreateInfo->enabledLayerCount = N_ENABLED_LAYERS_DEBUG;
	pCreateInfo->ppEnabledLayerNames = NAMES_ENABLED_LAYERS_DEBUG;
}
void vgSet_DebugExtensions(VkInstanceCreateInfo* pCreateInfo)
{
	//this debug messenger is seperate from the one that we use after instance creation
#ifdef DEBUG
	printf("\n\nPrinting requested extensions before requesting VK_EXT_DEBUG_UTILS_EXTENSION_NAME:");
	for (uint32_t i = 0; i < pCreateInfo->enabledExtensionCount; i++)
	{
		printf("\n\t%s", pCreateInfo->ppEnabledExtensionNames[i]);
	}
#endif // DEBUG

	uint32_t n_oldExts = pCreateInfo->enabledExtensionCount;
	uint32_t n_newExts = n_oldExts + 1;

	//WAIT am I causing a memory leak here?
	const char** Names_NewExts = (char**)malloc(sizeof(char*) * n_newExts); //I malloced here so need to free...
	//loop through through the old extensions
	for (uint32_t i = 0; i < n_oldExts; i++)
	{
		Names_NewExts[i] = pCreateInfo->ppEnabledExtensionNames[i];
	}
	Names_NewExts[n_newExts - 1] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;  //adding this one

	//alright let's set that stuff
	pCreateInfo->enabledExtensionCount = n_newExts;
	pCreateInfo->ppEnabledExtensionNames = Names_NewExts;
#ifdef DEBUG
	printf("\n\nPrinting requested extensions after adding VK_EXT_DEBUG_UTILS_EXTENSION_NAME");
	for (uint32_t i = 0; i < n_newExts; i++)
	{
		printf("\n\t%s", pCreateInfo->ppEnabledExtensionNames[i]);
	}
#endif // DEBUG

}


//CREATE. DESTROY in header
VkInstance vgCreate_Instance(VkAllocationCallbacks* pAllocator, uint32_t n_BaseRequiredEXTs, const char** names_BaseRequiredExts)
{
	VkApplicationInfo AppInfo = vgSet_AppInfo();
	VkInstanceCreateInfo CreateInfo = vgSet_CreateInfo(&AppInfo, n_BaseRequiredEXTs, names_BaseRequiredExts);
#ifdef DEBUG
	vgSet_Validation(&CreateInfo);  //adding the required validaiton layer(s)
	vgSet_DebugExtensions(&CreateInfo);

	//this is separate from the debug messenger created and destroyed after instance initialization
	VkDebugUtilsMessengerCreateInfoEXT DebugMessenger_InstanceCreation = vgSet_DebugMessengerInfo();
	CreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)& DebugMessenger_InstanceCreation;

	VkInstance hInstance;
	VkResult rezzy = vkCreateInstance(&CreateInfo, pAllocator, &hInstance);

	if (rezzy != VK_SUCCESS)
		printf("\nInstance creation failed!");
	else
		printf("\n\nyay");
#else
	VkInstance hInstance;
	VkResult rezzy = vkCreateInstance(&CreateInfo, pAllocator, &hInstance);
#endif // DEBUG

	assert(rezzy == VK_SUCCESS);  //nothing wrond with being assertive here I think
	return hInstance;
}
