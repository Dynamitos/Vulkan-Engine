#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>
#include <set>
#include <array>
#include <algorithm>
#include "display.h"

#define VK_CHECK(f)																						\
{																										\
	VkResult res = (f);																					\
	if (res != VK_SUCCESS)																				\
	{																									\
		std::cout << "Fatal : VkResult is \"" << res << "\" in " << __FILE__ << " at line " << __LINE__ << std::endl; \
		assert(res == VK_SUCCESS);																		\
	}																									\
}

VkBool32 __stdcall debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);

VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);

struct QueueFamilyIndices {
	int graphicsFamily = -1;
	int presentFamily = -1;
	int transferFamily = -1;
	int dedicatedTransfer = -1;
	bool isComplete() {
		return graphicsFamily >= 0 && presentFamily >= 0 && transferFamily >= 0;
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};
	static const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};
	static const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
namespace util
{
	

	std::vector<const char*> getRequiredExtensions();
	bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, Display* display);
	void createImageView(VkDevice device, VkImage image, VkFormat format, VkImageView& imageView);
}
namespace init
{
	VkApplicationInfo ApplicationInfo(
		const char* appName, 
		uint32_t appVersion,
		const char* engineName,
		uint32_t engineVersion,
		uint32_t apiVersion);

	VkInstanceCreateInfo InstanceCreateInfo(
		VkApplicationInfo* appInfo,
		std::vector<const char*> extensions,
		std::vector<const char*> layers);

	VkDebugReportCallbackCreateInfoEXT DebugReportCallbackCreateInfo(
		VkDebugReportFlagsEXT flags);

	VkDeviceQueueCreateInfo DeviceQueueCreateInfo(
		int queueFamilyIndex,
		int queueCount);

	VkDeviceQueueCreateInfo DeviceQueueCreateInfo(
		int queueFamilyIndex,
		int queueCount,
		float* queuePriority);

	VkDeviceCreateInfo DeviceCreateInfo(
		VkDeviceQueueCreateInfo* queueInfos,
		uint32_t queueCount,
		VkPhysicalDeviceFeatures* features,
		const char* const* deviceExtensions,
		uint32_t deviceExtensionCount,
		const char* const* layers,
		uint32_t layerCount);

	VkDeviceCreateInfo DeviceCreateInfo(
		VkDeviceQueueCreateInfo* queueInfos,
		uint32_t queueCount,
		VkPhysicalDeviceFeatures* features);

	VkSwapchainCreateInfoKHR SwapchainCreateInfo(
		VkSurfaceKHR surface,
		uint32_t minImageCount,
		VkFormat imageFormat,
		VkColorSpaceKHR colorSpace,
		VkExtent2D extent,
		uint32_t arrayLayers,
		VkImageUsageFlags usage,
		VkSurfaceTransformFlagBitsKHR transform,
		VkCompositeAlphaFlagBitsKHR alpha,
		VkPresentModeKHR presentMode,
		VkBool32 clipped);

	VkFramebufferCreateInfo FramebufferCreateInfo(
		VkRenderPass renderPass,
		uint32_t attachmentCount,
		VkImageView* attachments,
		uint32_t width,
		uint32_t height,
		uint32_t layers);

	VkAttachmentDescription AttachmentDescription(
		VkFormat format,
		VkSampleCountFlagBits sample,
		VkAttachmentLoadOp loadOp,
		VkAttachmentStoreOp storeOp,
		VkAttachmentLoadOp stencilLoadOp,
		VkAttachmentStoreOp stencilStoreOp,
		VkImageLayout imageLayout,
		VkImageLayout finalLayout);

	VkSubpassDescription SubpassDescription(
		VkPipelineBindPoint bindPoint,
		uint32_t colorAttachmentCount,
		VkAttachmentReference* colorReference,
		uint32_t depthAttachmentCount = 0,
		VkAttachmentReference* depthReference = nullptr,
		uint32_t inputAttachmentCount = 0,
		VkAttachmentReference* inputReference = nullptr,
		uint32_t resolveAttachmentCount = 0,
		VkAttachmentReference* resolveReference = nullptr,
		uint32_t preserveAttachmentCount = 0,
		VkAttachmentReference* preserveReference = nullptr);

	VkRenderPassCreateInfo RenderPassCreateInfo(
		uint32_t attachmentCount,
		VkAttachmentDescription* attachments,
		uint32_t subpassCount,
		VkSubpassDescription* subpasses,
		uint32_t dependencyCount,
		VkSubpassDependency* subpassDependencies);

	VkCommandPoolCreateInfo CommandPoolCreateInfo();
}