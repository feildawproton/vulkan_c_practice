#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string.h> //for string compare
#include <stdio.h> //for output and such
#include <stdlib.h> //forgot about malloc
#include <assert.h>

#include "debug_settings.h"
#include "vg_setup.h"


//BEGIN SECTION: SOME PRINTS
void print_availableEXT()
{
	uint32_t n_EXT = 0;
	VkResult rezzy = vkEnumerateInstanceExtensionProperties(NULL, &n_EXT, NULL);
	VkExtensionProperties* pExtensions = malloc(sizeof(VkExtensionProperties) * n_EXT);
	vkEnumerateInstanceExtensionProperties(NULL, &n_EXT, pExtensions);

	printf("\n\nPRINTING AVAILABLE EXTENSIONS");
	if (pExtensions != NULL)
	{
		for (uint32_t i = 0; i < n_EXT; i++)
		{
			printf("\n\t%s", pExtensions[i].extensionName);
		}
	}
	free(pExtensions);
}
void print_availableValidationLayers()
{
	uint32_t n_VAL = 0;
	VkResult rezzy = vkEnumerateInstanceLayerProperties(&n_VAL, NULL);
	VkLayerProperties* pLayers = malloc(sizeof(VkLayerProperties) * n_VAL);
	vkEnumerateInstanceLayerProperties(&n_VAL, pLayers);

	printf("\n\nPRINTING AVAILABLE VALIDATION LAYERS.");
	if (pLayers != NULL)
	{
		for (uint32_t i = 0; i < n_VAL; i++)
		{
			printf("\n\t%s", pLayers[i].layerName);
		}
	}
	free(pLayers);
}
void print_PhysicalDeviceLimits_v1_1(VkPhysicalDeviceLimits* pPhysicalDeviceLimits)
{
	printf("\n\tmaxImageDimension1D: %u", pPhysicalDeviceLimits->maxImageDimension1D);
	printf("\n\tmaxImageDimension2D: %u", pPhysicalDeviceLimits->maxImageDimension2D);
	printf("\n\tmaxImageDimension3D: %u", pPhysicalDeviceLimits->maxImageDimension3D);
	printf("\n\tmaxImageDimensionCube: %u", pPhysicalDeviceLimits->maxImageDimensionCube);
	printf("\n\tmaxImageArrayLayers: %u", pPhysicalDeviceLimits->maxImageArrayLayers);
	printf("\n\tmaxTexelBufferElements: %u", pPhysicalDeviceLimits->maxTexelBufferElements);
	printf("\n\tmaxUniformBufferRange: %u", pPhysicalDeviceLimits->maxUniformBufferRange);
	printf("\n\tmaxStorageBufferRange: %u", pPhysicalDeviceLimits->maxStorageBufferRange);
	printf("\n\tmaxPushConstantsSize: %u", pPhysicalDeviceLimits->maxPushConstantsSize);
	printf("\n\tmaxMemoryAllocationCount: %u", pPhysicalDeviceLimits->maxMemoryAllocationCount);
	printf("\n\tmaxSamplerAllocationCount: %u", pPhysicalDeviceLimits->maxSamplerAllocationCount);
	printf("\n\tbufferImageGranularity: %llu", pPhysicalDeviceLimits->bufferImageGranularity);
	printf("\n\tsparseAddressSpaceSize: %llu", pPhysicalDeviceLimits->sparseAddressSpaceSize);
	printf("\n\tmaxBoundDescriptorSets: %u", pPhysicalDeviceLimits->maxBoundDescriptorSets);
	printf("\n\tmaxPerStageDescriptorSamplers: %u", pPhysicalDeviceLimits->maxPerStageDescriptorSamplers);
	printf("\n\tmaxPerStageDescriptorUniformBuffers: %u", pPhysicalDeviceLimits->maxPerStageDescriptorUniformBuffers);
	printf("\n\tmaxPerStageDescriptorStorageBuffers: %u", pPhysicalDeviceLimits->maxPerStageDescriptorStorageBuffers);
	printf("\n\tmaxPerStageDescriptorSampledImages: %u", pPhysicalDeviceLimits->maxPerStageDescriptorSampledImages);
	printf("\n\tmaxPerStageDescriptorStorageImages: %u", pPhysicalDeviceLimits->maxPerStageDescriptorStorageImages);
	printf("\n\tmaxPerStageDescriptorInputAttachments: %u", pPhysicalDeviceLimits->maxPerStageDescriptorInputAttachments);
	printf("\n\tmaxPerStageResources: %u", pPhysicalDeviceLimits->maxPerStageResources);
	printf("\n\tmaxDescriptorSetSamplers: %u", pPhysicalDeviceLimits->maxDescriptorSetSamplers);
	printf("\n\tmaxDescriptorSetUniformBuffers: %u", pPhysicalDeviceLimits->maxDescriptorSetUniformBuffers);
	printf("\n\tmaxDescriptorSetUniformBuffersDynamic: %u", pPhysicalDeviceLimits->maxDescriptorSetUniformBuffersDynamic);
	printf("\n\tmaxDescriptorSetStorageBuffers: %u", pPhysicalDeviceLimits->maxDescriptorSetStorageBuffers);
	printf("\n\tmaxDescriptorSetStorageBuffersDynamic: %u", pPhysicalDeviceLimits->maxDescriptorSetStorageBuffersDynamic);
	printf("\n\tmaxDescriptorSetSampledImages: %u", pPhysicalDeviceLimits->maxDescriptorSetSampledImages);
	printf("\n\tmaxDescriptorSetStorageImages: %u", pPhysicalDeviceLimits->maxDescriptorSetStorageImages);
	printf("\n\tmaxDescriptorSetInputAttachments: %u", pPhysicalDeviceLimits->maxDescriptorSetInputAttachments);
	printf("\n\tmaxVertexInputAttributes: %u", pPhysicalDeviceLimits->maxVertexInputAttributes);
	printf("\n\tmaxVertexInputBindings: %u", pPhysicalDeviceLimits->maxVertexInputBindings);
	printf("\n\tmaxVertexInputAttributeOffset: %u", pPhysicalDeviceLimits->maxVertexInputAttributeOffset);
	printf("\n\tmaxVertexInputBindingStride: %u", pPhysicalDeviceLimits->maxVertexInputBindingStride);
	printf("\n\tmaxVertexOutputComponents: %u", pPhysicalDeviceLimits->maxVertexOutputComponents);
	printf("\n\tmaxTessellationGenerationLevel: %u", pPhysicalDeviceLimits->maxTessellationGenerationLevel);
	printf("\n\tmaxTessellationPatchSize: %u", pPhysicalDeviceLimits->maxTessellationPatchSize);
	printf("\n\tmaxTessellationControlPerVertexInputComponents: %u", pPhysicalDeviceLimits->maxTessellationControlPerVertexInputComponents);
	printf("\n\tmaxTessellationControlPerVertexOutputComponents: %u", pPhysicalDeviceLimits->maxTessellationControlPerVertexOutputComponents);
	printf("\n\tmaxTessellationControlPerPatchOutputComponents: %u", pPhysicalDeviceLimits->maxTessellationControlPerPatchOutputComponents);
	printf("\n\tmaxTessellationControlTotalOutputComponents: %u", pPhysicalDeviceLimits->maxTessellationControlTotalOutputComponents);
	printf("\n\tmaxTessellationEvaluationInputComponents: %u", pPhysicalDeviceLimits->maxTessellationEvaluationInputComponents);
	printf("\n\tmaxTessellationEvaluationOutputComponents: %u", pPhysicalDeviceLimits->maxTessellationEvaluationOutputComponents);
	printf("\n\tmaxGeometryShaderInvocations: %u", pPhysicalDeviceLimits->maxGeometryShaderInvocations);
	printf("\n\tmaxGeometryInputComponents: %u", pPhysicalDeviceLimits->maxGeometryInputComponents);
	printf("\n\tmaxGeometryOutputComponents: %u", pPhysicalDeviceLimits->maxGeometryOutputComponents);
	printf("\n\tmaxGeometryOutputVertices: %u", pPhysicalDeviceLimits->maxGeometryOutputVertices);
	printf("\n\tmaxGeometryTotalOutputComponents: %u", pPhysicalDeviceLimits->maxGeometryTotalOutputComponents);
	printf("\n\tmaxFragmentInputComponents: %u", pPhysicalDeviceLimits->maxFragmentInputComponents);
	printf("\n\tmaxFragmentOutputAttachments: %u", pPhysicalDeviceLimits->maxFragmentOutputAttachments);
	printf("\n\tmaxFragmentDualSrcAttachments: %u", pPhysicalDeviceLimits->maxFragmentDualSrcAttachments);
	printf("\n\tmaxFragmentCombinedOutputResources: %u", pPhysicalDeviceLimits->maxFragmentCombinedOutputResources);
	printf("\n\tmaxComputeSharedMemorySize: %u", pPhysicalDeviceLimits->maxComputeSharedMemorySize);
	printf("\n\tmaxComputeWorkGroupCount[0]: %u", pPhysicalDeviceLimits->maxComputeWorkGroupCount[0]);
	printf("\n\tmaxComputeWorkGroupCount[1]: %u", pPhysicalDeviceLimits->maxComputeWorkGroupCount[1]);
	printf("\n\tmaxComputeWorkGroupCount[2]: %u", pPhysicalDeviceLimits->maxComputeWorkGroupCount[2]);
	printf("\n\tmaxComputeWorkGroupInvocations: %u", pPhysicalDeviceLimits->maxComputeWorkGroupInvocations);
	printf("\n\tmaxComputeWorkGroupSize[0]: %u", pPhysicalDeviceLimits->maxComputeWorkGroupSize[0]);
	printf("\n\tmaxComputeWorkGroupSize[1]: %u", pPhysicalDeviceLimits->maxComputeWorkGroupSize[1]);
	printf("\n\tmaxComputeWorkGroupSize[2]: %u", pPhysicalDeviceLimits->maxComputeWorkGroupSize[2]);
	printf("\n\tsubPixelPrecisionBits: %u", pPhysicalDeviceLimits->subPixelPrecisionBits);
	printf("\n\tsubTexelPrecisionBits: %u", pPhysicalDeviceLimits->subTexelPrecisionBits);
	printf("\n\tmipmapPrecisionBits: %u", pPhysicalDeviceLimits->mipmapPrecisionBits);
	printf("\n\tmaxDrawIndexedIndexValue: %u", pPhysicalDeviceLimits->maxDrawIndexedIndexValue);
	printf("\n\tmaxDrawIndirectCount: %u", pPhysicalDeviceLimits->maxDrawIndirectCount);
	printf("\n\tmaxSamplerLodBias: %f", pPhysicalDeviceLimits->maxSamplerLodBias);
	printf("\n\tmaxSamplerAnisotropy: %f", pPhysicalDeviceLimits->maxSamplerAnisotropy);
	printf("\n\tmaxViewports: %u", pPhysicalDeviceLimits->maxViewports);
	printf("\n\tmaxViewportDimensions[0]: %u", pPhysicalDeviceLimits->maxViewportDimensions[0]);
	printf("\n\tmaxViewportDimensions[1]: %u", pPhysicalDeviceLimits->maxViewportDimensions[1]);
	printf("\n\tviewportBoundsRange[0]: %f", pPhysicalDeviceLimits->viewportBoundsRange[0]);
	printf("\n\tviewportBoundsRange[1]: %f", pPhysicalDeviceLimits->viewportBoundsRange[1]);
	printf("\n\tviewportSubPixelBits: %u", pPhysicalDeviceLimits->viewportSubPixelBits);
	printf("\n\tminMemoryMapAlignment: %zu", pPhysicalDeviceLimits->minMemoryMapAlignment);
	printf("\n\tminTexelBufferOffsetAlignment: %llu", pPhysicalDeviceLimits->minTexelBufferOffsetAlignment);
	printf("\n\tminUniformBufferOffsetAlignment: %llu", pPhysicalDeviceLimits->minUniformBufferOffsetAlignment);
	printf("\n\tminStorageBufferOffsetAlignment: %llu", pPhysicalDeviceLimits->minStorageBufferOffsetAlignment);
	printf("\n\tminTexelOffset: %i", pPhysicalDeviceLimits->minTexelOffset);
	printf("\n\tmaxTexelOffset: %u", pPhysicalDeviceLimits->maxTexelOffset);
	printf("\n\tminTexelGatherOffset: %i", pPhysicalDeviceLimits->minTexelGatherOffset);
	printf("\n\tmaxTexelGatherOffset: %u", pPhysicalDeviceLimits->maxTexelGatherOffset);
	printf("\n\tminInterpolationOffset: %f", pPhysicalDeviceLimits->minInterpolationOffset);
	printf("\n\tmaxInterpolationOffset: %f", pPhysicalDeviceLimits->maxInterpolationOffset);
	printf("\n\tsubPixelInterpolationOffsetBits: %u", pPhysicalDeviceLimits->subPixelInterpolationOffsetBits);
	printf("\n\tmaxFramebufferWidth: %u", pPhysicalDeviceLimits->maxFramebufferWidth);
	printf("\n\tmaxFramebufferHeight: %u", pPhysicalDeviceLimits->maxFramebufferHeight);
	printf("\n\tmaxFramebufferLayers: %u", pPhysicalDeviceLimits->maxFramebufferLayers);
	printf("\n\tframebufferColorSampleCounts: %u", pPhysicalDeviceLimits->framebufferColorSampleCounts);
	printf("\n\tframebufferDepthSampleCounts: %u", pPhysicalDeviceLimits->framebufferDepthSampleCounts);
	printf("\n\tframebufferStencilSampleCounts: %u", pPhysicalDeviceLimits->framebufferStencilSampleCounts);
	printf("\n\tframebufferNoAttachmentsSampleCounts: %u", pPhysicalDeviceLimits->framebufferNoAttachmentsSampleCounts);
	printf("\n\tmaxColorAttachments: %u", pPhysicalDeviceLimits->maxColorAttachments);
	printf("\n\tsampledImageColorSampleCounts: %u", pPhysicalDeviceLimits->sampledImageColorSampleCounts);
	printf("\n\tsampledImageIntegerSampleCounts: %u", pPhysicalDeviceLimits->sampledImageIntegerSampleCounts);
	printf("\n\tsampledImageDepthSampleCounts: %u", pPhysicalDeviceLimits->sampledImageDepthSampleCounts);
	printf("\n\tsampledImageStencilSampleCounts: %u", pPhysicalDeviceLimits->sampledImageStencilSampleCounts);
	printf("\n\tstorageImageSampleCounts: %u", pPhysicalDeviceLimits->storageImageSampleCounts);
	printf("\n\tmaxSampleMaskWords: %u", pPhysicalDeviceLimits->maxSampleMaskWords);
	printf("\n\ttimestampComputeAndGraphics: %u", pPhysicalDeviceLimits->timestampComputeAndGraphics); //vkbool32
	printf("\n\ttimestampPeriod: %f", pPhysicalDeviceLimits->timestampPeriod);
	printf("\n\tmaxClipDistances: %u", pPhysicalDeviceLimits->maxClipDistances);
	printf("\n\tmaxCullDistances: %u", pPhysicalDeviceLimits->maxCullDistances);
	printf("\n\tmaxCombinedClipAndCullDistances: %u", pPhysicalDeviceLimits->maxCombinedClipAndCullDistances);
	printf("\n\tdiscreteQueuePriorities: %u", pPhysicalDeviceLimits->discreteQueuePriorities);
	printf("\n\tpointSizeRange[0]: %f", pPhysicalDeviceLimits->pointSizeRange[0]);
	printf("\n\tpointSizeRange[1]: %f", pPhysicalDeviceLimits->pointSizeRange[1]);
	printf("\n\tlineWidthRange[0]: %f", pPhysicalDeviceLimits->lineWidthRange[0]);
	printf("\n\tlineWidthRange[1]: %f", pPhysicalDeviceLimits->lineWidthRange[1]);
	printf("\n\tpointSizeGranularity: %f", pPhysicalDeviceLimits->pointSizeGranularity);
	printf("\n\tlineWidthGranularity: %f", pPhysicalDeviceLimits->lineWidthGranularity);
	printf("\n\tstrictLines: %u", pPhysicalDeviceLimits->strictLines); //vkbool32
	printf("\n\tstandardSampleLocations: %u", pPhysicalDeviceLimits->standardSampleLocations); //vkbool32
	printf("\n\toptimalBufferCopyOffsetAlignment: %llu", pPhysicalDeviceLimits->optimalBufferCopyOffsetAlignment);
	printf("\n\toptimalBufferCopyRowPitchAlignment: %llu", pPhysicalDeviceLimits->optimalBufferCopyRowPitchAlignment);
	printf("\n\tnonCoherentAtomSize: %llu", pPhysicalDeviceLimits->nonCoherentAtomSize);
}

void print_PhysicalDeviceFeatures_V1_1(VkPhysicalDeviceFeatures* pPhysicalDeviceFeatures)
{
	printf("\n\trobustBufferAccess: %u", pPhysicalDeviceFeatures->robustBufferAccess);
	printf("\n\tfullDrawIndexUint32: %u", pPhysicalDeviceFeatures->fullDrawIndexUint32);
	printf("\n\timageCubeArray: %u", pPhysicalDeviceFeatures->imageCubeArray);
	printf("\n\tindependentBlend: %u", pPhysicalDeviceFeatures->independentBlend);
	printf("\n\tgeometryShader: %u", pPhysicalDeviceFeatures->geometryShader);
	printf("\n\ttessellationShader: %u", pPhysicalDeviceFeatures->tessellationShader);
	printf("\n\tsampleRateShading: %u", pPhysicalDeviceFeatures->sampleRateShading);
	printf("\n\tdualSrcBlend: %u", pPhysicalDeviceFeatures->dualSrcBlend);
	printf("\n\tlogicOp: %u", pPhysicalDeviceFeatures->logicOp);
	printf("\n\tmultiDrawIndirect: %u", pPhysicalDeviceFeatures->multiDrawIndirect);
	printf("\n\tdrawIndirectFirstInstance: %u", pPhysicalDeviceFeatures->drawIndirectFirstInstance);
	printf("\n\tdepthClamp: %u", pPhysicalDeviceFeatures->depthClamp);
	printf("\n\tdepthBiasClamp: %u", pPhysicalDeviceFeatures->depthBiasClamp);
	printf("\n\tfillModeNonSolid: %u", pPhysicalDeviceFeatures->fillModeNonSolid);
	printf("\n\tdepthBounds: %u", pPhysicalDeviceFeatures->depthBounds);
	printf("\n\twideLines: %u", pPhysicalDeviceFeatures->wideLines);
	printf("\n\tlargePoints: %u", pPhysicalDeviceFeatures->largePoints);
	printf("\n\talphaToOne: %u", pPhysicalDeviceFeatures->alphaToOne);
	printf("\n\tmultiViewport: %u", pPhysicalDeviceFeatures->multiViewport);
	printf("\n\tsamplerAnisotropy: %u", pPhysicalDeviceFeatures->samplerAnisotropy);
	printf("\n\ttextureCompressionETC2: %u", pPhysicalDeviceFeatures->textureCompressionETC2);
	printf("\n\ttextureCompressionASTC_LDR: %u", pPhysicalDeviceFeatures->textureCompressionASTC_LDR);
	printf("\n\ttextureCompressionBC: %u", pPhysicalDeviceFeatures->textureCompressionBC);
	printf("\n\tocclusionQueryPrecise: %u", pPhysicalDeviceFeatures->occlusionQueryPrecise);
	printf("\n\tpipelineStatisticsQuery: %u", pPhysicalDeviceFeatures->pipelineStatisticsQuery);
	printf("\n\tvertexPipelineStoresAndAtomics: %u", pPhysicalDeviceFeatures->vertexPipelineStoresAndAtomics);
	printf("\n\tfragmentStoresAndAtomics: %u", pPhysicalDeviceFeatures->fragmentStoresAndAtomics);
	printf("\n\tshaderTessellationAndGeometryPointSize: %u", pPhysicalDeviceFeatures->shaderTessellationAndGeometryPointSize);
	printf("\n\tshaderImageGatherExtended: %u", pPhysicalDeviceFeatures->shaderImageGatherExtended);
	printf("\n\tshaderStorageImageExtendedFormats: %u", pPhysicalDeviceFeatures->shaderStorageImageExtendedFormats);
	printf("\n\tshaderStorageImageMultisample: %u", pPhysicalDeviceFeatures->shaderStorageImageMultisample);
	printf("\n\tshaderStorageImageReadWithoutFormat: %u", pPhysicalDeviceFeatures->shaderStorageImageReadWithoutFormat);
	printf("\n\tsthaderStorageImageWriteWithoutFormat: %u", pPhysicalDeviceFeatures->shaderStorageImageWriteWithoutFormat);
	printf("\n\tshaderUniformBufferArrayDynamicIndexing: %u", pPhysicalDeviceFeatures->shaderUniformBufferArrayDynamicIndexing);
	printf("\n\tshaderSampledImageArrayDynamicIndexing: %u", pPhysicalDeviceFeatures->shaderSampledImageArrayDynamicIndexing);
	printf("\n\tshaderStorageBufferArrayDynamicIndexing: %u", pPhysicalDeviceFeatures->shaderStorageBufferArrayDynamicIndexing);
	printf("\n\tshaderStorageImageArrayDynamicIndexing: %u", pPhysicalDeviceFeatures->shaderStorageImageArrayDynamicIndexing);
	printf("\n\tshaderClipDistance: %u", pPhysicalDeviceFeatures->shaderClipDistance);
	printf("\n\tshaderCullDistance: %u", pPhysicalDeviceFeatures->shaderCullDistance);
	printf("\n\tshaderFloat64: %u", pPhysicalDeviceFeatures->shaderFloat64);
	printf("\n\tshaderInt64: %u", pPhysicalDeviceFeatures->shaderInt64);
	printf("\n\tshaderInt16: %u", pPhysicalDeviceFeatures->shaderInt16);
	printf("\n\tshaderResourceResidency: %u", pPhysicalDeviceFeatures->shaderResourceResidency);
	printf("\n\tshaderResourceMinLod: %u", pPhysicalDeviceFeatures->shaderResourceMinLod);
	printf("\n\tsparseBinding: %u", pPhysicalDeviceFeatures->sparseBinding);
	printf("\n\tsparseResidencyBuffer: %u", pPhysicalDeviceFeatures->sparseResidencyBuffer);
	printf("\n\tsparseResidencyImage2D: %u", pPhysicalDeviceFeatures->sparseResidencyImage2D);
	printf("\n\tsparseResidencyImage3D: %u", pPhysicalDeviceFeatures->sparseResidencyImage3D);
	printf("\n\tsparseResidency2Samples: %u", pPhysicalDeviceFeatures->sparseResidency2Samples);
	printf("\n\tsparseResidency4Samples: %u", pPhysicalDeviceFeatures->sparseResidency4Samples);
	printf("\n\tsparseResidency8Samples: %u", pPhysicalDeviceFeatures->sparseResidency8Samples);
	printf("\n\tsparseResidency16Samples: %u", pPhysicalDeviceFeatures->sparseResidency16Samples);
	printf("\n\tsparseResidencyAliased: %u", pPhysicalDeviceFeatures->sparseResidencyAliased);
	printf("\n\tvariableMultisampleRate: %u", pPhysicalDeviceFeatures->variableMultisampleRate);
	printf("\n\tinheritedQueries: %u", pPhysicalDeviceFeatures->inheritedQueries);
}
void print_PhysicalDeviceQueueFamilyProperties_v1_1(uint32_t count_qFamiles, VkQueueFamilyProperties* pQFamiliesProperties)
{
	for (uint32_t i = 0; i < count_qFamiles; i++)
	{
		printf("\n\nPrinting information for queue family %u of %u", (i + 1), count_qFamiles);
		printf("\n\tqueueFlags: %u", pQFamiliesProperties[i].queueFlags);
		//as of v1_1 VK_QUEUE_GRAPHICS_BIT = 0x00000001;
		if (pQFamiliesProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			printf("\n\t\tPresent: VK_QUEUE_GRAPHICS_BIT");
		else
			printf("\n\t\tNOT present: VK_QUEUE_GRAPHICS_BIT");
		//as of v1_1 VK_QUEUE_COMPUTE_BIT = 0x00000002;
		if (pQFamiliesProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
			printf("\n\t\tPresent: VK_QUEUE_COMPUTE_BIT");
		else
			printf("\n\t\tNOT present: VK_QUEUE_COMPUTE_BIT");
		//as of v1_1 VK_QUEUE_TRANSFER_BIT  = 0x00000004;
		if (pQFamiliesProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
			printf("\n\t\tPresent: VK_QUEUE_TRANSFER_BIT ");
		else
			printf("\n\t\tNOT present: VK_QUEUE_TRANSFER_BIT ");
		//as of v1_1 VK_QUEUE_SPARSE_BINDING_BIT = 0x00000008;
		if (pQFamiliesProperties[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
			printf("\n\t\tPresent: VK_QUEUE_SPARSE_BINDING_BIT");
		else
			printf("\n\t\tNOT present: VK_QUEUE_SPARSE_BINDING_BIT");
		//as of v1_1 VK_QUEUE_PROTECTED_BIT = 0x00000010;
		if (pQFamiliesProperties[i].queueFlags & VK_QUEUE_PROTECTED_BIT)
			printf("\n\t\tPresent: VK_QUEUE_PROTECTED_BIT");
		else
			printf("\n\t\tNOT present: VK_QUEUE_PROTECTED_BIT");
		printf("\n\tqueueCount: %u", pQFamiliesProperties[i].queueCount);
		printf("\n\ttimestampValidBits: %u", pQFamiliesProperties[i].timestampValidBits);
		printf("\n\tminImageTransferGranularity width: %u", pQFamiliesProperties[i].minImageTransferGranularity.width);
		printf("\n\tminImageTransferGranularity height: %u", pQFamiliesProperties[i].minImageTransferGranularity.height);
		printf("\n\tminImageTransferGranularity depth: %u", pQFamiliesProperties[i].minImageTransferGranularity.depth);
	}
}
void print_availableDevices_v1_1(VkInstance hInstance)
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(hInstance, &deviceCount, NULL);
	VkPhysicalDevice* pDevices = malloc(sizeof(VkPhysicalDevice) * deviceCount);
	vkEnumeratePhysicalDevices(hInstance, &deviceCount, pDevices);
	printf("\n\nPrinting the available physical device properties for %u devices.", deviceCount);
	for (uint32_t i = 0; i < deviceCount; i++)
	{
		VkPhysicalDeviceProperties DeviceProperties;

		vkGetPhysicalDeviceProperties(pDevices[i], &DeviceProperties);

		printf("\n\nPRINTING PHYSICAL PROPERTIES OF DEVICE %s", DeviceProperties.deviceName);
		printf("\n\tAPI Version: %i", DeviceProperties.apiVersion);
		printf("\n\tDriver Version: %i", DeviceProperties.driverVersion);
		printf("\n\tVender ID: %i", DeviceProperties.vendorID);
		printf("\n\tDevice ID: %i", DeviceProperties.deviceID);
		printf("\n\tDevice Type: %i", DeviceProperties.deviceType);  //VkPhysicalDeviceType this is an enum that describes it as discrete, integrated, etc
		printf("\n\tDevice name: %s", DeviceProperties.deviceName);
		printf("\n\tDevice pipeline UUID: %hhu", DeviceProperties.pipelineCacheUUID);

		printf("\n\nPRINTING PHYSICAL LIMITS OF DEVICE %s:", DeviceProperties.deviceName);  //has things like maxImageDimension2d, mipmapPrecisionBits, and many more
		print_PhysicalDeviceLimits_v1_1(&DeviceProperties.limits);

		printf("\n\nPRINTING DEVICE SPARSE PROPERTIES FOR %s:", DeviceProperties.deviceName);
		printf("\n\tresidencyStandard2DBlockShape: %u", DeviceProperties.sparseProperties.residencyStandard2DBlockShape);
		printf("\n\tresidencyStandard2DMultisampleBlockShape: %u", DeviceProperties.sparseProperties.residencyStandard2DMultisampleBlockShape);
		printf("\n\tresidencyStandard3DBlockShape: %u", DeviceProperties.sparseProperties.residencyStandard3DBlockShape);
		printf("\n\tresidencyAlignedMipSize: %u", DeviceProperties.sparseProperties.residencyAlignedMipSize);
		printf("\n\tresidencyNonResidentStrict: %u", DeviceProperties.sparseProperties.residencyNonResidentStrict);

		printf("\n\nPRINTING DEVICE FEATURES FOR %s:", DeviceProperties.deviceName);
		VkPhysicalDeviceFeatures DeviceFeatures;
		vkGetPhysicalDeviceFeatures(pDevices[i], &DeviceFeatures);
		print_PhysicalDeviceFeatures_V1_1(&DeviceFeatures);

		printf("\n\nPRINTING DEVICE QUEUE FAMILY PROPERTIES FOR %s:", DeviceProperties.deviceName);
		uint32_t count_qFamilies = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(pDevices[i], &count_qFamilies, NULL);
		VkQueueFamilyProperties* pQFamiliesProperties = malloc(sizeof(VkQueueFamilyProperties) * count_qFamilies);
		vkGetPhysicalDeviceQueueFamilyProperties(pDevices[i], &count_qFamilies, pQFamiliesProperties);
		print_PhysicalDeviceQueueFamilyProperties_v1_1(count_qFamilies, pQFamiliesProperties);

		free(pQFamiliesProperties);
	}
	free(pDevices);
}
void print_DeviceUsage(hVgDeviceQueueFamiliesUsage hDeviceUsage)
{
	printf("\n\nPrinting current queue usage of devie:");
	for (uint32_t i = 0; i < hDeviceUsage->N_QueueFamilies; i++)
	{
		printf("\n\tUsage information for queue family %u of %u", (i + 1), hDeviceUsage->N_QueueFamilies, hDeviceUsage->QueueFlags[i]);
		printf("\n\t\t%u Total Queues available to family", hDeviceUsage->pMaxQ[i]);
		uint32_t n_graphics = hDeviceUsage->pN_Graphics[i];
		uint32_t n_compute = hDeviceUsage->pN_Compute[i];
		uint32_t n_transfer = hDeviceUsage->pN_Transfer[i];
		uint32_t n_sparse = hDeviceUsage->pN_Sparse[i];
		uint32_t n_protected = hDeviceUsage->pN_Protected[i];
		printf("\n\t\t%u Total Queues in use for family", (n_graphics + n_compute + n_transfer + n_sparse + n_protected));
		if (hDeviceUsage->QueueFlags[i] & VK_QUEUE_GRAPHICS_BIT)
			printf("\n\t\t%u GRAPHICS queues in use", n_graphics);
		if (hDeviceUsage->QueueFlags[i] & VK_QUEUE_COMPUTE_BIT)
			printf("\n\t\t%u COMPUTE queues in use", n_compute);
		if (hDeviceUsage->QueueFlags[i] & VK_QUEUE_TRANSFER_BIT)
			printf("\n\t\t%u TRANSFER queues in use", n_transfer);
		if (hDeviceUsage->QueueFlags[i] & VK_QUEUE_SPARSE_BINDING_BIT)
			printf("\n\t\t%u SPARSE BINDING queues in use", n_sparse);
		if (hDeviceUsage->QueueFlags[i] & VK_QUEUE_PROTECTED_BIT)
			printf("\n\t\t%u PROTECTED queues in use", n_protected);

	}
}
//END SECTION: SOME PRINTS





//BEGIN SECTION: SELECTIONS
VkPhysicalDevice select_UserGPU(VkInstance hInstance)
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(hInstance, &deviceCount, NULL);
	VkPhysicalDevice* pDevices = malloc(sizeof(VkPhysicalDevice) * deviceCount);
	vkEnumeratePhysicalDevices(hInstance, &deviceCount, pDevices);
	printf("\n\nPlease select a GPU by entering a number below:");

	int32_t selection = 0;
	for (uint32_t i = 0; i < deviceCount; i++)
	{
		VkPhysicalDeviceProperties DeviceProperties;
		vkGetPhysicalDeviceProperties(pDevices[i], &DeviceProperties);
		printf("\nPress %u for: %s", i, DeviceProperties.deviceName);
	}
	printf("\n\nSelection: ");
	selection = getchar();

	//okay let's check that the selection is valid
	VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
	if (selection >= deviceCount || selection < 0)
		PhysicalDevice = pDevices[0];
	else
		PhysicalDevice = pDevices[selection];

	free(pDevices);

	//let's make sure that I didn't do anything silly
	VkPhysicalDeviceProperties DevicePropoerties;
	vkGetPhysicalDeviceProperties(PhysicalDevice, &DevicePropoerties);
	printf("\n\nSelected device %s", DevicePropoerties.deviceName);

	return PhysicalDevice;
}
//END SECTION: SELECTIONS


//BEGIN SECTION: QUEUE AND LOGICAL DEVICE STRUCTURES
VkDeviceQueueCreateInfo fill_QueueInfo(VkPhysicalDevice hDevice)
{

}
//END SECTION: QUEUE AND LOGICAL DEVICE



//VkQueueFlags is a bitmask type for 0 or more VkQueueFlagBits
void create_LogicalDevice(VkQueueFlags Flags)
{
	//typedef enum VkQueueFlagBits {
	//	VK_QUEUE_GRAPHICS_BIT = 0x00000001,
	//	VK_QUEUE_COMPUTE_BIT = 0x00000002,
	//	VK_QUEUE_TRANSFER_BIT = 0x00000004,
	//	VK_QUEUE_SPARSE_BINDING_BIT = 0x00000008,
	//	VK_QUEUE_PROTECTED_BIT = 0x00000010,
	//	VK_QUEUE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
	//} VkQueueFlagBits;
}

int main(const uint32_t argc, const char** argv)
{
	//BEGIN SECTION: SOME PRE WORK BEFORE INIT
	print_availableEXT();  //printing just for fun
	print_availableValidationLayers();  //again just for fun

	//END SECTION: SOME PRE WORK BEFORE INIT


	//INITIALIZE SECTION
	//1
	GLFWwindow* pMyWindow = vgInitCreate_GLFWwindow();  //do i really need to do this first...

	//2
	uint32_t n_BaseRequiredEXTs = 0;
	const char** names_BaseRequiredEXTs = get_GLFWExtension(&n_BaseRequiredEXTs);
	VkInstance hInstance = vgCreate_Instance(NULL, n_BaseRequiredEXTs, names_BaseRequiredEXTs);  //there will be a debug messenger here that is different than the one that we create below

	//3
	VkDebugUtilsMessengerEXT DebugMessenger = vgCreate_DebugMessenger(hInstance, NULL);

	//:4 Select Physical
	print_availableDevices_v1_1(hInstance);
	VkPhysicalDevice hDevice = select_UserGPU(hInstance);

	//5: Create Logical Device
	hVgDeviceQueueFamiliesUsage hDeviceUsage = vgCreate_DeviceUsageTracker(hDevice);
	print_DeviceUsage(hDeviceUsage);

	//MAIN LOOP
	while (!glfwWindowShouldClose(pMyWindow))
		glfwPollEvents();

	//CLEANUP SECTION

	//5:
	vgDestroy_DeviceUsageTracker(hDeviceUsage);


	//4: Unpick the physical device...

	//3: DebugMessenger Destroy
	vgDestroy_DebugMessenger(hInstance, DebugMessenger, NULL);
	//2: VkInstance Destroy
	vgDestroy_Instance(hInstance, NULL);

	//1: Window Destroy:
	vgDestroyTerminate_GLFWwindow(pMyWindow);

	return 0;
}