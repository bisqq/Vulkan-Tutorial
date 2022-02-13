#pragma once

#include <stdint.h>
#include <optional>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <array>


#ifndef VULKRON
#define VULKRON

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/hash.hpp"

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "VulkronVertex.h"
#include "stb_image.h"
#include "tiny_obj_loader.h"


struct QueueFamilyIndices 
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

struct SwapChainSupportDetails 
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct UniformBufferObject
{
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

struct VulkronApplicationInfo {
    bool               enableValidationLayers;
    uint32_t           major;
    uint32_t           minor;
    uint32_t           patch;
};


struct Vulkron
{
//=========================================================================================================================
//  Instance & Window Surface
//=========================================================================================================================

private:
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();

protected:
    void createInstance();
    void setupDebugMessenger();
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    void createSurface();

//=========================================================================================================================
//  Device
//=========================================================================================================================

private:
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

protected:
    void getAllPhysicalDevices();
    void createLogicalDevice();

//=========================================================================================================================
//  Queue
//=========================================================================================================================

private:
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

//=========================================================================================================================
//  Swap Chain
//=========================================================================================================================

private:
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    void recreateSwapChain();

protected:
    void createSwapChain();
    void cleanUpSwapChain();

//=========================================================================================================================
//  Image Views
//=========================================================================================================================

protected:
    void createImageViews();

//=========================================================================================================================
//  Graphics Pipeline
//=========================================================================================================================

private:
    VkShaderModule createShaderModule(const std::vector<char>& code);
    static std::vector<char> readFile(const std::string& filename);

protected:
    void createGuiGraphicsPipeline();
    void createGraphicsPipeline();
    void createRenderPass();

//=========================================================================================================================
//  Frame Buffers
//=========================================================================================================================
    
protected:
    void createFramebuffers();

//=========================================================================================================================
//  Command Buffers
//=========================================================================================================================

protected:
    void createCommandPool();
    void createCommandBuffers();

//=========================================================================================================================
//  Draw
//=========================================================================================================================

protected:
    void drawFrame();
    void createSyncObjects();

//=========================================================================================================================
//  Vertex Buffer
//=========================================================================================================================

private:
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

protected:
    void createVertexBuffer();
    void createIndexBuffer();

//=========================================================================================================================
//  Uniform Buffer
//=========================================================================================================================

private:
    void updateUniformBuffer(uint32_t currentImage);

protected:
    void createUniformBuffers();
    void createDescriptorSetLayout();
    void createDescriptorPool();
    void createDescriptorSets();

//=========================================================================================================================
//  Textures
//=========================================================================================================================

private:
    void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format,
        VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
    VkCommandBuffer beginSingleTimeCommands();
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);

protected:
    void createTextureImage();
    void createTextureImageView();
    void createTextureSampler();

//=========================================================================================================================
//  Depth Buffering
//=========================================================================================================================

private:
    VkFormat findDepthFormat();
    bool hasStencilComponent(VkFormat format);
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

protected:
    void createDepthResources();

//=========================================================================================================================
//  Loading Models
//=========================================================================================================================

protected:
    void loadModel();

//=========================================================================================================================
//  Mipmaps
//=========================================================================================================================

private:
    void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

//=========================================================================================================================
//  Multisamplings
//=========================================================================================================================

private:
    VkSampleCountFlagBits getMaxUsableSampleCount();

protected:
    void createColorResources();

//=========================================================================================================================
//=========================================================================================================================

private:
    //test
    const std::string MODEL_PATH =   "file/path/here";
    const std::string TEXTURE_PATH = "file/path/here";

    //shaders
    const std::string SCENE_VERT = "file/path/here";
    const std::string SCENE_FRAG = "file/path/here";

//=========================================================================================================================
//=========================================================================================================================

public:
	GLFWwindow* window;
    std::vector<VulkronVertex> vertices;
    std::vector<uint32_t> indices;

protected:
    VulkronApplicationInfo vkAppInfo;

protected:
	const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
	const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
    const int MAX_FRAMES_IN_FLIGHT = 2;
    bool framebufferResized = false;
    size_t currentFrame = 0;

protected:
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    VkCommandPool commandPool;

    VkImage colorImage;
    VkDeviceMemory colorImageMemory;
    VkImageView colorImageView;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    uint32_t mipLevels;
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;

};

#endif // !VULKRON

namespace std {
    template<> struct hash<VulkronVertex> {
        size_t operator()(VulkronVertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}


