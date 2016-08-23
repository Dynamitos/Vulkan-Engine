#include "utils.h"

VkApplicationInfo init::ApplicationInfo(const char* appName, uint32_t appVersion, const char* engineName, uint32_t engineVersion, uint32_t apiVersion)
{
	VkApplicationInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info.pApplicationName = appName;
	info.applicationVersion = appVersion;
	info.pEngineName = engineName;
	info.engineVersion = engineVersion;
	info.apiVersion = apiVersion;
	return info;
}

VkInstanceCreateInfo init::InstanceCreateInfo(VkApplicationInfo* appInfo, std::vector<const char*> extensions, std::vector<const char*> layers)
{
	VkInstanceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	info.pApplicationInfo = appInfo;
	info.enabledExtensionCount = extensions.size();
	info.ppEnabledExtensionNames = extensions.data();
	info.enabledLayerCount = layers.size();
	info.ppEnabledLayerNames = layers.data();
	return info;
}

VkDebugReportCallbackCreateInfoEXT init::DebugReportCallbackCreateInfo(VkDebugReportFlagsEXT flags)
{
	VkDebugReportCallbackCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	createInfo.flags = flags;
	createInfo.pfnCallback = (PFN_vkDebugReportCallbackEXT)debugCallback;
	return createInfo;
}

VkDeviceQueueCreateInfo init::DeviceQueueCreateInfo(int queueFamilyIndex, int queueCount)
{
	float priority = 1.0f;
	return DeviceQueueCreateInfo(queueFamilyIndex, queueCount, &priority);
}

VkDeviceQueueCreateInfo init::DeviceQueueCreateInfo(int queueFamilyIndex, int queueCount, float * queuePriority)
{
	VkDeviceQueueCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	createInfo.queueFamilyIndex = queueFamilyIndex;
	createInfo.queueCount = 1;
	createInfo.pQueuePriorities = queuePriority;
	return createInfo;
}

VkDeviceCreateInfo init::DeviceCreateInfo(VkDeviceQueueCreateInfo * queueInfos, uint32_t queueCount, VkPhysicalDeviceFeatures * features)
{
	return DeviceCreateInfo(queueInfos, queueCount, features, deviceExtensions.data(), (uint32_t)deviceExtensions.size(), validationLayers.data(), (uint32_t)validationLayers.size());
}

VkSwapchainCreateInfoKHR init::SwapchainCreateInfo(VkSurfaceKHR surface, uint32_t minImageCount, VkFormat imageFormat, VkColorSpaceKHR colorSpace, VkExtent2D extent, uint32_t arrayLayers, VkImageUsageFlags usage, VkSurfaceTransformFlagBitsKHR transform, VkCompositeAlphaFlagBitsKHR alpha, VkPresentModeKHR presentMode, VkBool32 clipped)
{
	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.surface = surface;
	createInfo.minImageCount = minImageCount;
	createInfo.imageFormat = imageFormat;
	createInfo.imageColorSpace = colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = arrayLayers;
	createInfo.imageUsage = usage;
	createInfo.preTransform = transform;
	createInfo.compositeAlpha = alpha;
	createInfo.presentMode = presentMode;
	createInfo.clipped = clipped;
	return createInfo;
}

VkFramebufferCreateInfo init::FramebufferCreateInfo(VkRenderPass renderPass, uint32_t attachmentCount, VkImageView * attachments, uint32_t width, uint32_t height, uint32_t layers)
{
	VkFramebufferCreateInfo createInfo = {};
	VkFramebufferCreateInfo frameBufferCreateInfo = {};
	frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	frameBufferCreateInfo.pNext = nullptr;
	frameBufferCreateInfo.renderPass = renderPass;
	frameBufferCreateInfo.attachmentCount = attachmentCount;
	frameBufferCreateInfo.pAttachments = attachments;
	frameBufferCreateInfo.width = width;
	frameBufferCreateInfo.height = height;
	frameBufferCreateInfo.layers = layers;
	return frameBufferCreateInfo;
}

VkAttachmentDescription init::AttachmentDescription(VkFormat format, VkSampleCountFlagBits sample, VkAttachmentLoadOp loadOp, VkAttachmentStoreOp storeOp, VkAttachmentLoadOp stencilLoadOp, VkAttachmentStoreOp stencilStoreOp, VkImageLayout imageLayout, VkImageLayout finalLayout)
{
	VkAttachmentDescription desc = {};
	desc.format = format;
	desc.samples = sample;
	desc.loadOp = loadOp;
	desc.storeOp = storeOp;
	desc.stencilLoadOp = stencilLoadOp;
	desc.stencilStoreOp = stencilStoreOp;
	desc.initialLayout = imageLayout;
	desc.finalLayout = finalLayout;
	return desc;
}

VkSubpassDescription init::SubpassDescription(VkPipelineBindPoint bindPoint, uint32_t colorAttachmentCount, VkAttachmentReference * colorReference, uint32_t depthAttachmentCount, VkAttachmentReference * depthReference, uint32_t inputAttachmentCount, VkAttachmentReference * inputReference, uint32_t resolveAttachmentCount, VkAttachmentReference * resolveReference, uint32_t preserveAttachmentCount, VkAttachmentReference * preserveReference)
{
	VkSubpassDescription desc = {};
	desc.pipelineBindPoint = bindPoint;
	desc.colorAttachmentCount = colorAttachmentCount;
	desc.pColorAttachments = colorReference;
	return desc;
}

VkRenderPassCreateInfo init::RenderPassCreateInfo(uint32_t attachmentCount, VkAttachmentDescription * attachments, uint32_t subpassCount, VkSubpassDescription * subpasses, uint32_t dependencyCount, VkSubpassDependency * subpassDependencies)
{
	VkRenderPassCreateInfo info = {};
	info.attachmentCount = attachmentCount;
	info.pAttachments = attachments;
	info.subpassCount = subpassCount;
	info.pSubpasses = subpasses;
	info.dependencyCount = dependencyCount;
	info.pDependencies = subpassDependencies;
	
	return info;
}

VkCommandPoolCreateInfo init::CommandPoolCreateInfo()
{
	VkCommandPoolCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	return info;
}

VkDeviceCreateInfo init::DeviceCreateInfo(VkDeviceQueueCreateInfo * queueInfos, uint32_t queueCount, VkPhysicalDeviceFeatures * features, const char * const* deviceExtensions, uint32_t deviceExtensionCount, const char * const* layers, uint32_t layerCount)
{
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueInfos;
	createInfo.queueCreateInfoCount = queueCount;

	createInfo.pEnabledFeatures = features;

	createInfo.ppEnabledExtensionNames = deviceExtensions;
	createInfo.enabledExtensionCount = deviceExtensionCount;

	
	createInfo.enabledLayerCount = layerCount;
	createInfo.ppEnabledLayerNames = layers;
	
	return createInfo;
}

std::vector<const char*> util::getRequiredExtensions()
{
	std::vector<const char*> extensions;

	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	for (unsigned int i = 0; i < glfwExtensionCount; i++) {
		extensions.push_back(glfwExtensions[i]);
	}

	extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	

	return extensions;
}
bool util::isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface)
{
	QueueFamilyIndices indices = findQueueFamilies(device, surface);

	bool extensionsSupported = checkDeviceExtensionSupport(device);
	bool swapChainAdequate = false;
	if (extensionsSupported) {
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}
	return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool util::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}
QueueFamilyIndices util::findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
	int i = 0;
	for (const auto& queueFamily : queueFamilies)
	{
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			indices.graphicsFamily = i;
		}
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
		{
			indices.transferFamily = i;
		}
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

		if (queueFamily.queueCount > 0 && presentSupport)
		{
			indices.presentFamily = i;
		}
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT == 0) 
		{
			indices.dedicatedTransfer = i;
		}

		i++;
	}

	if (indices.dedicatedTransfer != -1)
		indices.transferFamily = indices.dedicatedTransfer;
	return indices;
}

SwapChainSupportDetails util::querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
{
	SwapChainSupportDetails details;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
	}
	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
	}

	return details;
}

VkSurfaceFormatKHR util::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	VkSurfaceFormatKHR format;
	if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED)
	{
		return{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLORSPACE_SRGB_NONLINEAR_KHR };
	}
	for (const auto& availableFormat : availableFormats)
	{
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}
	return availableFormats[0];
}
VkPresentModeKHR util::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
{
	for (const auto& availablePresentMode : availablePresentModes)
	{
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return availablePresentMode;
		}
	}
	return VK_PRESENT_MODE_FIFO_KHR;
}
VkExtent2D util::chooseSwapExtent(const VkSurfaceCapabilitiesKHR & capabilities, Display* display)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	}
	else {
		VkExtent2D actualExtent = { display->getWidth(), display->getHeight() };

		actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

		return actualExtent;
	}
}

void util::createImageView(VkDevice device, VkImage image, VkFormat format, VkImageView & imageView)
{
	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VK_CHECK(vkCreateImageView(device, &viewInfo, nullptr, &imageView));
}

VkBool32 __stdcall debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
	std::cerr << "validation layer: " << msg << std::endl;

	return VK_FALSE;
}
VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
	auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pCallback);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}