#pragma once

#include "Vulkron.h"

struct VulkronPrintDebug: private Vulkron
{
	void printStats(VkPhysicalDevice& device);
	void printInstanceLayers();
	void printInstanceExtensions();
};