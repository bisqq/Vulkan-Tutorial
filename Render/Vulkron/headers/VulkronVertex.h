#pragma once

#include "vulkan/vulkan.h"
#include "glm/glm.hpp"

#include <array>

struct VulkronVertex
{
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	VulkronVertex()
		:pos(), color(), texCoord()
	{}

	VulkronVertex(glm::vec3 pos_, glm::vec3 color_, glm::vec2 texCoord_)
		: pos(pos_), color(color_), texCoord(texCoord_)
	{}

	static VkVertexInputBindingDescription getBindingDescription()
	{
		VkVertexInputBindingDescription VertexInputBindingDescription;

		VertexInputBindingDescription.binding = 0;
		VertexInputBindingDescription.stride = sizeof(VulkronVertex);
		VertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return VertexInputBindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescription()
	{
		std::array<VkVertexInputAttributeDescription, 3> VertexInputAttributeDescriptions{};

        VertexInputAttributeDescriptions[0].binding = 0;
        VertexInputAttributeDescriptions[0].location = 0;
        VertexInputAttributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        VertexInputAttributeDescriptions[0].offset = offsetof(VulkronVertex, pos);

        VertexInputAttributeDescriptions[1].binding = 0;
        VertexInputAttributeDescriptions[1].location = 1;
        VertexInputAttributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        VertexInputAttributeDescriptions[1].offset = offsetof(VulkronVertex, color);

        VertexInputAttributeDescriptions[2].binding = 0;
        VertexInputAttributeDescriptions[2].location = 2;
        VertexInputAttributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        VertexInputAttributeDescriptions[2].offset = offsetof(VulkronVertex, texCoord);

		return VertexInputAttributeDescriptions;
	}

	bool operator==(const VulkronVertex& other) const {
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}
};