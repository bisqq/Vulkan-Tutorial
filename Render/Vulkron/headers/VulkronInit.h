#pragma once

#include "Vulkron.h"

struct VulkronInit: public Vulkron
{
	void beginVulkan();
	void beginDrawFrame();
	void shutdownVulkan();

public:
	VulkronApplicationInfo Info;
};