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

	VkMemoryAllocateInfo MemoryAllocateInfo(
		uint32_t size, 
		VkMemoryType type);

	VkCommandBufferAllocateInfo CommandBufferAllocateInfo(
		VkCommandPool cmdPool,
		VkCommandBufferLevel level,
		uint32_t bufferCount);

	VkCommandPoolCreateInfo CommandPoolCreateInfo();

	VkCommandBufferBeginInfo CommandBufferBeginInfo();

	VkCommandBufferInheritanceInfo CommandBufferInheritanceInfo();

	VkRenderPassBeginInfo RenderPassBeginInfo();

	VkRenderPassCreateInfo RenderPassCreateInfo();

	VkImageMemoryBarrier ImageMemoryBarrier();

	VkBufferMemoryBarrier BufferMemoryBarrier();

	VkMemoryBarrier MemoryBarrier();

	VkImageCreateInfo ImageCreateInfo();

	VkSamplerCreateInfo SamplerCreateInfo();

	VkImageViewCreateInfo ImageViewCreateInfo();

	VkSemaphoreCreateInfo SemaphoreCreateInfo();

	VkFenceCreateInfo FenceCreateInfo(
		VkFenceCreateFlags flags);

	VkEventCreateInfo EventCreateInfo();

	VkSubmitInfo SubmitInfo();

	VkViewport Viewport(
		float width,
		float height,
		float minDepth,
		float maxDepth);

	VkRect2D Rect2D(
		int32_t width,
		int32_t height,
		int32_t offsetX,
		int32_t offsetY);

	VkBufferCreateInfo BufferCreateInfo();

	VkBufferCreateInfo BufferCreateInfo(
		VkBufferUsageFlags usage,
		VkDeviceSize size);
	
	VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo(
		uint32_t poolSizeCount,
		VkDescriptorPoolSize* pPoolSizes,
		uint32_t maxSets);

	VkDescriptorPoolSize DescriptorPoolSize(
		VkDescriptorType type, 
		uint32_t descriptorCount);

	VkDescriptorSetLayoutBinding DescriptorSetLayoutBinding(
		VkDescriptorType type,
		VkShaderStageFlags stageFlags,
		uint32_t binding,
		uint32_t count);

	VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo(
		const VkDescriptorSetLayoutBinding* pBindings,
		uint32_t bindingCount);

	VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo(
		const VkDescriptorSetLayout* pSetLayouts,
		uint32_t setLayoutCount);

	VkDescriptorSetAllocateInfo DescriptorSetAllocateInfo(
		VkDescriptorPool descriptorPool,
		const VkDescriptorSetLayout* pSetLayouts,
		uint32_t descriptorSetCount);

	VkDescriptorImageInfo DescriptorImageInfo(
		VkSampler sampler,
		VkImageView imageView,
		VkImageLayout imageLayout);

	VkWriteDescriptorSet WriteDescriptorSet(
		VkDescriptorSet dstSet,
		VkDescriptorType type,
		uint32_t binding,
		VkDescriptorBufferInfo* bufferInfo);

	VkWriteDescriptorSet WriteDescriptorSet(
		VkDescriptorSet dstSet,
		VkDescriptorType type,
		uint32_t binding,
		VkDescriptorImageInfo* bufferInfo);

	VkVertexInputBindingDescription VertexInputBindingDescription(
		uint32_t binding, 
		uint32_t stride, 
		VkVertexInputRate inputRate);

		VkVertexInputAttributeDescription VertexInputAttributeDescription(
		uint32_t binding,
		uint32_t location,
		VkFormat format,
		uint32_t offset);

		VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo();

	VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo(
		VkPrimitiveTopology topology,
		VkPipelineInputAssemblyStateCreateFlags flags,
		VkBool32 primitiveRestartEnable);

	VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateCreateInfo(
		VkPolygonMode polygonMode,
		VkCullModeFlags cullMode,
		VkFrontFace frontFace,
		VkPipelineRasterizationStateCreateFlags flags);

	VkPipelineColorBlendAttachmentState PipelineColorBlendAttachmentState(
		VkColorComponentFlags colorWriteMask,
		VkBool32 blendEnable);

	VkPipelineColorBlendStateCreateInfo PipelineColorBlendStateCreateInfo(
		uint32_t attachmentCount,
		const VkPipelineColorBlendAttachmentState * pAttachments);

	VkPipelineDepthStencilStateCreateInfo PipelineDepthStencilStateCreateInfo(
		VkBool32 depthTestEnable,
		VkBool32 depthWriteEnable,
		VkCompareOp depthCompareOp);

	VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo(
		uint32_t viewportCount,
		uint32_t scissorCount,
		VkPipelineViewportStateCreateFlags flags);

	VkPipelineMultisampleStateCreateInfo PipelineMultisampleStateCreateInfo(
		VkSampleCountFlagBits rasterizationSamples,
		VkPipelineMultisampleStateCreateFlags flags);

	VkPipelineDynamicStateCreateInfo PipelineDynamicStateCreateInfo(
		const VkDynamicState * pDynamicStates,
		uint32_t dynamicStateCount,
		VkPipelineDynamicStateCreateFlags flags);

	VkPipelineTessellationStateCreateInfo PipelineTessellationStateCreateInfo(
		uint32_t patchControlPoints);

	VkGraphicsPipelineCreateInfo PipelineCreateInfo(
		VkPipelineLayout layout,
		VkRenderPass renderPass,
		VkPipelineCreateFlags flags);

	VkComputePipelineCreateInfo ComputePipelineCreateInfo(
		VkPipelineLayout layout, 
		VkPipelineCreateFlags flags);

	VkPushConstantRange PushConstantRange(
		VkShaderStageFlags stageFlags,
		uint32_t size,
		uint32_t offset);

}