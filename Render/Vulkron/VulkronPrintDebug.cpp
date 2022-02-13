
#include "VulkronPrintDebug.h"
#include "Macros/Macros.h"


void VulkronPrintDebug::printStats(VkPhysicalDevice& device)
{
	VkPhysicalDeviceProperties properties;
	vkGetPhysicalDeviceProperties(device, &properties);

	uint32_t apiVer = properties.apiVersion;

	LOG("Name:                    " << properties.deviceName);
	LOG("API Version:             " << VK_VERSION_MAJOR(apiVer) << "." << VK_VERSION_MINOR(apiVer) << "." << VK_VERSION_PATCH(apiVer));
	LOG("Driver Version:          " << properties.driverVersion);
	LOG("Vendor ID:               " << properties.vendorID);
	LOG("Device ID:               " << properties.deviceID);
	LOG("Device Type:             " << properties.deviceType);
	LOG("discreteQueuePriorities: " << properties.limits.discreteQueuePriorities);

	VkPhysicalDeviceFeatures features;
	vkGetPhysicalDeviceFeatures(device, &features);
	LOG("Geometry Shader: " << features.geometryShader);

	VkPhysicalDeviceMemoryProperties memoryProperties;
	vkGetPhysicalDeviceMemoryProperties(device, &memoryProperties);

	uint32_t amountOfQueueFamilies = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &amountOfQueueFamilies, nullptr);
	VkQueueFamilyProperties* familyProperties = new VkQueueFamilyProperties[amountOfQueueFamilies];
	vkGetPhysicalDeviceQueueFamilyProperties(device, &amountOfQueueFamilies, familyProperties);

	LOG("Amount of Queue Families: " << amountOfQueueFamilies);

	for (int i = 0; i < amountOfQueueFamilies; i++)
	{
		LOG("");
		LOG("Queue family #" << i);
		LOG("VK_QUEUE_GRAPHICS_BIT       " << ((familyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0));
		LOG("VK_QUEUE_COMPUTE_BIT        " << ((familyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) != 0));
		LOG("VK_QUEUE_TRANSFER_BIT       " << ((familyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT) != 0));
		LOG("VK_QUEUE_SPARSE_BINDING_BIT " << ((familyProperties[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) != 0));
		LOG("Queue Count:                " << familyProperties[i].queueCount);
		LOG("Timestamp Valid Bits:       " << familyProperties[i].timestampValidBits);

		uint32_t width = familyProperties[i].minImageTransferGranularity.width;
		uint32_t height = familyProperties[i].minImageTransferGranularity.height;
		uint32_t depth = familyProperties[i].minImageTransferGranularity.depth;

		LOG("Min Image Transfer Grtanularity: " << width << "," << height << "," << depth);

	}

	VkSurfaceCapabilitiesKHR surfaceCapabilites;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &surfaceCapabilites);
	LOG("Surface capabilites: ");
	LOG("\tminImageCount:           " << surfaceCapabilites.minImageCount);
	LOG("\tmaxImageCount:           " << surfaceCapabilites.maxImageCount);
	LOG("\tcurrentExtent:           " << surfaceCapabilites.currentExtent.width << "/" << surfaceCapabilites.currentExtent.height);
	LOG("\tminImageExtent:          " << surfaceCapabilites.minImageExtent.width << "/" << surfaceCapabilites.minImageExtent.height);
	LOG("\tmaxImageExtent:          " << surfaceCapabilites.maxImageExtent.width << "/" << surfaceCapabilites.maxImageExtent.height);
	LOG("\tmaxImageArrayLayers:     " << surfaceCapabilites.maxImageArrayLayers);
	LOG("\tsupportedTransforms:     " << surfaceCapabilites.supportedTransforms);
	LOG("\tcurrentTransform:        " << surfaceCapabilites.currentTransform);
	LOG("\tsupportedCompositeAlpha: " << surfaceCapabilites.supportedCompositeAlpha);
	LOG("\tsupportedUsageFlags:     " << surfaceCapabilites.supportedUsageFlags);

	uint32_t amounfOfFormats = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &amounfOfFormats, nullptr);
	VkSurfaceFormatKHR* surfaceFormats = new VkSurfaceFormatKHR[amounfOfFormats];
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &amounfOfFormats, surfaceFormats);

	LOG("");
	LOG("Amount of Formats: " << amounfOfFormats);
	for (int i = 0; i < amounfOfFormats; i++)
	{
		LOG("Format: " << surfaceFormats[i].format);
	}

	uint32_t amountOfPresentationsModes = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &amountOfPresentationsModes, nullptr);
	VkPresentModeKHR* presentModes = new VkPresentModeKHR[amountOfPresentationsModes];
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &amountOfPresentationsModes, presentModes);

	LOG("");
	LOG("Amount of Presentation Modes: " << amountOfPresentationsModes);
	for (int i = 0; i < amountOfPresentationsModes; i++)
	{
		LOG("Supported presentation mode: " << presentModes[i]);
	}

	LOG("");
	delete[] familyProperties;
	delete[] surfaceFormats;
	delete[] presentModes;
}

void VulkronPrintDebug::printInstanceLayers()
{
	uint32_t amountOfLayers = 0;
	vkEnumerateInstanceLayerProperties(&amountOfLayers, nullptr);
	VkLayerProperties* layers = new VkLayerProperties[amountOfLayers];
	vkEnumerateInstanceLayerProperties(&amountOfLayers, layers);

	LOG("Amount of Instance Layers: " << amountOfLayers);
	for (int i = 0; i < amountOfLayers; i++)
	{
		LOG("");
		LOG("Name:         " << layers[i].layerName);
		LOG("Spec Version: " << layers[i].specVersion);
		LOG("Impl Version: " << layers[i].implementationVersion);
		LOG("Description:  " << layers[i].description);
	}

	delete layers;
}

void VulkronPrintDebug::printInstanceExtensions()
{
	uint32_t amountOfExtensions = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &amountOfExtensions, nullptr);
	VkExtensionProperties* extensions = new VkExtensionProperties[amountOfExtensions];
	vkEnumerateInstanceExtensionProperties(nullptr, &amountOfExtensions, extensions);

	LOG("");
	LOG("Amount of Extensions: " << amountOfExtensions);
	for (int i = 0; i < amountOfExtensions; i++)
	{
		LOG("");
		LOG("Name:         " << extensions[i].extensionName);
		LOG("Spec Version: " << extensions[i].specVersion);
	}

	delete[] extensions;
}