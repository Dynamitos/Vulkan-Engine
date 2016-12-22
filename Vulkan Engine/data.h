#pragma once
#include <vulkan\vulkan.h>
#include <map>
#include <memory>
#include <mutex>
#include <vector>
#include "display.h"

struct QueueFamilyIndices {
	int graphicsFamily = -1;
	int presentFamily = -1;
	int transferFamily = -1;
	int dedicatedTransfer = -1;
	bool isComplete() {
		return graphicsFamily >= 0 && presentFamily >= 0 && transferFamily >= 0;
	}
};

struct VulkanContext
{
	Display* display;
	VkInstance instance;
	VkPhysicalDevice physicalDevice;
	VkDevice device;
	VkDebugReportCallbackEXT callback;
	VkSurfaceKHR surface;
	VkCommandPool commandPool;
	VkCommandPool cmdTempPool;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkQueue transferQueue;
	VkSwapchainKHR swapChain;
	VkExtent2D swapChainExtent;
	VkFormat swapChainImageFormat;
	VkRenderPass renderPass;
	VkImage depthImage;
	VkDeviceMemory depthMemory;
	VkImageView depthImageView;
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> frameBuffers;
	std::vector<VkCommandBuffer> commandBuffers;
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	QueueFamilyIndices indices;
};
class Data
{
public:
	virtual ~Data();
	static Data& getInstance();
	//std::vector<Renderable*> renderTargets;//fill with data
	VulkanContext* getContext();
private:
	VulkanContext* context;
	static std::unique_ptr<Data> m_instance;
	static std::once_flag m_onceFlag;
	Data(void);
	Data(const Data& src);
};