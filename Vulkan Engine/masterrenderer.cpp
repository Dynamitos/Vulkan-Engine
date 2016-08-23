#include "masterrenderer.h"

MasterRenderer::MasterRenderer()
	:display{ new Display() } {
	display->createDisplay();
	initInstance();
	setupDebugCallback();
	createSurface();
	pickPhysicalDevice();
	createLogicalDevice();
	createSwapChain();
	createRenderPass();
	createFramebuffers();
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::initInstance()
{
	VkApplicationInfo appInfo =
		init::ApplicationInfo(
			"Vulkan Engine",
			VK_MAKE_VERSION(1, 0, 0),
			"Worst Engine Ever",
			VK_MAKE_VERSION(1, 0, 0),
			VK_API_VERSION_1_0);

	VkInstanceCreateInfo createInfo =
		init::InstanceCreateInfo(
			&appInfo,
			util::getRequiredExtensions(),
			validationLayers);

	VK_CHECK(vkCreateInstance(&createInfo, nullptr, &instance));
}

void MasterRenderer::setupDebugCallback()
{
	VkDebugReportCallbackCreateInfoEXT createInfo =
		init::DebugReportCallbackCreateInfo(
			VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT);

	VK_CHECK(CreateDebugReportCallbackEXT(instance, &createInfo, nullptr, &callback));
}

void MasterRenderer::createSurface()
{
	VK_CHECK(glfwCreateWindowSurface(instance, display->getWindow(), nullptr, &surface));
}

void MasterRenderer::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for (const auto& device : devices) {
		if (util::isDeviceSuitable(device, surface)) {
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}
}

void MasterRenderer::createLogicalDevice()
{
	QueueFamilyIndices indices = util::findQueueFamilies(physicalDevice, surface);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<int> uniqueQueueFamilies = { indices.graphicsFamily, indices.presentFamily, indices.transferFamily };

	for (int queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo = 
			init::DeviceQueueCreateInfo(
				queueFamily,
				1);
		queueCreateInfos.push_back(queueCreateInfo);
	}
	VkPhysicalDeviceFeatures deviceFeatures = {};

	VkDeviceCreateInfo createInfo =
		init::DeviceCreateInfo(
			queueCreateInfos.data(),
			queueCreateInfos.size(),
			&deviceFeatures);

	VK_CHECK(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device));

	vkGetDeviceQueue(device, indices.graphicsFamily, 0, &graphicsQueue);
	vkGetDeviceQueue(device, indices.presentFamily, 0, &presentQueue);
	vkGetDeviceQueue(device, indices.transferFamily, 0, &transferQueue);
}

void MasterRenderer::createSwapChain()
{
	SwapChainSupportDetails swapChainSupport = util::querySwapChainSupport(physicalDevice, surface);

	VkSurfaceFormatKHR surfaceFormat = util::chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = util::chooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = util::chooseSwapExtent(swapChainSupport.capabilities, display);

	swapChainImageFormat = surfaceFormat.format;
	swapChainExtent = extent;

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
	{
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}
	VkSwapchainCreateInfoKHR createInfo =
		init::SwapchainCreateInfo(
			surface,
			imageCount,
			surfaceFormat.format,
			surfaceFormat.colorSpace,
			extent,
			1,
			VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
			swapChainSupport.capabilities.currentTransform,
			VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
			presentMode,
			VK_TRUE);
	QueueFamilyIndices indices = util::findQueueFamilies(physicalDevice, surface);
	uint32_t queueFamilyIndices[] = { (uint32_t)indices.graphicsFamily, (uint32_t)indices.presentFamily };

	if (indices.graphicsFamily != indices.presentFamily)
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional
	}
	VkSwapchainKHR oldSwapChain = swapChain;
	createInfo.oldSwapchain = oldSwapChain;
	
	VkSwapchainKHR newSwapChain;
	VK_CHECK(vkCreateSwapchainKHR(device, &createInfo, nullptr, &newSwapChain));
	*&swapChain = newSwapChain;

	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
	swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());
}

void MasterRenderer::createRenderPass()
{
	VkAttachmentDescription attachment =
		init::AttachmentDescription(
			swapChainImageFormat,
			VK_SAMPLE_COUNT_1_BIT,
			VK_ATTACHMENT_LOAD_OP_CLEAR,
			VK_ATTACHMENT_STORE_OP_STORE,
			VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			VK_ATTACHMENT_STORE_OP_DONT_CARE,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

	VkAttachmentReference colorReference = {};
	colorReference.attachment = 0;
	colorReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpassDescription =
		init::SubpassDescription(
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			1,
			&colorReference);

	std::array<VkSubpassDependency, 2> dependencies;

	dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
	dependencies[0].dstSubpass = 0;
	dependencies[0].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
	dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependencies[0].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
	dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

	dependencies[1].srcSubpass = 0;
	dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
	dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependencies[1].dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
	dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	dependencies[1].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
	dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

	VkRenderPassCreateInfo createInfo =
		init::RenderPassCreateInfo(
			1,
			&attachment,
			1,
			&subpassDescription,
			static_cast<uint32_t>(dependencies.size()),
			dependencies.data());

	VK_CHECK(vkCreateRenderPass(device, &createInfo, nullptr, &renderPass));
}
void MasterRenderer::createFramebuffers()
{
	VkImageView attachments;
	frameBuffers.resize(swapChainImages.size());
	VkFramebufferCreateInfo createInfo =
		init::FramebufferCreateInfo(
			renderPass,
			1,
			&attachments,
			display->getWidth(),
			display->getHeight(),
			1);
	for (uint32_t i = 0; i < frameBuffers.size(); i++)
	{
		util::createImageView(device, swapChainImages[i], swapChainImageFormat, attachments);
		VK_CHECK(vkCreateFramebuffer(device, &createInfo, nullptr, &frameBuffers[i]))
	}
}

