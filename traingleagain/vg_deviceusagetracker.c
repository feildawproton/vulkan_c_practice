#include "vg_setup.h"

#include <stdlib.h>

//this is to track usage.  Hopefully I will remember to require all functions that create queues to require this struct
//don't think I need to take the address of the device because it is already a handle
hVgDeviceQueueFamiliesUsage vgCreate_DeviceUsageTracker(VkPhysicalDevice hDevice)
{
	//i want to return a pointer so allocate
	hVgDeviceQueueFamiliesUsage hDeviceUsage = (hVgDeviceQueueFamiliesUsage)malloc(sizeof(struct VgDeviceQueueFamiliesUsage));

	uint32_t count_qFamilies = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(hDevice, &count_qFamilies, NULL);
	VkQueueFamilyProperties* pQFamiliesProperties = (VkQueueFamilyProperties*)malloc(sizeof(VkQueueFamilyProperties) * count_qFamilies);
	vkGetPhysicalDeviceQueueFamilyProperties(hDevice, &count_qFamilies, pQFamiliesProperties);

	hDeviceUsage->N_QueueFamilies = count_qFamilies;
	hDeviceUsage->QueueFlags = (VkQueueFlags*)malloc(sizeof(VkQueueFlags) * count_qFamilies);
	hDeviceUsage->pMaxQ = (uint32_t*)malloc(sizeof(uint32_t) * count_qFamilies);
	hDeviceUsage->pN_Graphics = (uint32_t*)malloc(sizeof(uint32_t) * count_qFamilies);
	hDeviceUsage->pN_Compute = (uint32_t*)malloc(sizeof(uint32_t) * count_qFamilies);
	hDeviceUsage->pN_Transfer = (uint32_t*)malloc(sizeof(uint32_t) * count_qFamilies);
	hDeviceUsage->pN_Sparse = (uint32_t*)malloc(sizeof(uint32_t) * count_qFamilies);
	hDeviceUsage->pN_Protected = (uint32_t*)malloc(sizeof(uint32_t) * count_qFamilies);

	for (uint32_t i = 0; i < count_qFamilies; i++)
	{
		hDeviceUsage->QueueFlags[i] = pQFamiliesProperties[i].queueFlags;
		hDeviceUsage->pMaxQ[i] = pQFamiliesProperties[i].queueCount;
		hDeviceUsage->pN_Graphics[i] = 0;
		hDeviceUsage->pN_Compute[i] = 0;
		hDeviceUsage->pN_Transfer[i] = 0;
		hDeviceUsage->pN_Sparse[i] = 0;
		hDeviceUsage->pN_Protected[i] = 0;
	}

	free(pQFamiliesProperties);

	return hDeviceUsage;
}
void vgDestroy_DeviceUsageTracker(hVgDeviceQueueFamiliesUsage hDeviceUsage)
{
	free(hDeviceUsage->QueueFlags);
	free(hDeviceUsage->pMaxQ);
	free(hDeviceUsage->pN_Graphics);
	free(hDeviceUsage->pN_Compute);
	free(hDeviceUsage->pN_Transfer);
	free(hDeviceUsage->pN_Sparse);
	free(hDeviceUsage->pN_Protected);
}