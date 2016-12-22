#include "masterrenderer.h"

<<<<<<< HEAD
bool MasterRenderer::leftMouseDown;
bool MasterRenderer::rightMouseDown;

=======
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
MasterRenderer::MasterRenderer() {
	context = Data::getInstance().getContext();
	context->display = new Display();
	context->display->createDisplay();
	tileRenderer = new TileRenderer();
<<<<<<< HEAD
	terrainRenderer = new TerrainRenderer();
	glfwSetWindowUserPointer(context->display->getWindow(), this);
	glfwSetWindowSizeCallback(context->display->getWindow(), &MasterRenderer::windowResized);
	glfwSetMouseButtonCallback(context->display->getWindow(), &MasterRenderer::mousePressed);
	glfwSetKeyCallback(context->display->getWindow(), &MasterRenderer::keyPressed);
	glfwSetCursorPosCallback(context->display->getWindow(), &MasterRenderer::mouseMove);
	camera = new Camera();
	camera->setPerspective(70.f, context->display->getWidth() / context->display->getHeight(), 0.01f, 1000.f);
=======
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
	initInstance();
	setupDebugCallback();
	createSurface();
	pickPhysicalDevice();
	createLogicalDevice();
	createSwapChain();
	createImageViews();
	createRenderPass();
	tileRenderer->createDescriptorSetLayout();
	tileRenderer->createGraphicsPipeline();
<<<<<<< HEAD
	terrainRenderer->createDescriptorSetLayout();
	terrainRenderer->createGraphicsPipeline();
	createCommandPools();
	createDepthResources();
	createFramebuffers();
	tileRenderer->createShaderData();
	tileRenderer->createDescriptorPool();
	tileRenderer->createDescriptorSet();
	terrainRenderer->createShaderData();
	terrainRenderer->createDescriptorPool();
	terrainRenderer->createDescriptorSet();
	createSemaphores();
	while (!glfwWindowShouldClose(context->display->getWindow()))
	{

		auto startTime = std::chrono::high_resolution_clock::now();
		render();
		auto endTime = std::chrono::high_resolution_clock::now();
		auto diffTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
		frameTimer = (float)diffTime / 1000.f;
		camera->update(frameTimer);
		if (camera->moving())
		{
			camera->viewChanged = true;
		}
=======
	createFramebuffers();
	createCommandPools();
	tileRenderer->createShaderData();
	tileRenderer->createDescriptorPool();
	tileRenderer->createDescriptorSet();
	createSemaphores();
	while (!glfwWindowShouldClose(context->display->getWindow()))
	{
		render();
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
		context->display->updateDisplay();
	}
	context->display->closeDisplay();
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::render()
{
	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(context->device, context->swapChain, std::numeric_limits<uint64_t>::max(), context->imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);


	VkSemaphore waitSemaphores[] = { context->imageAvailableSemaphore };
	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		recreateSwapChain();
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}
	VkSubmitInfo submitInfo =
		init::SubmitInfo();

	createCommandBuffer(context->frameBuffers[imageIndex]);

	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &primaryCommandBuffer;


	VkSemaphore signalSemaphores[] = { context->renderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	if (vkQueueSubmit(context->graphicsQueue, 1, &submitInfo, renderFence) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}
	
	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { context->swapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;
	VkResult fenceRes;
	do
	{
		fenceRes = vkWaitForFences(context->device, 1, &renderFence, VK_TRUE, 100000000);
	} while (fenceRes == VK_TIMEOUT);

	result = vkQueuePresentKHR(context->presentQueue, &presentInfo);

	vkResetFences(context->device, 1, &renderFence);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
		recreateSwapChain();
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}
}

void MasterRenderer::initInstance()
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Vulkan Test";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Worst Engine Ever";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = util::getRequiredExtensions();
	createInfo.enabledExtensionCount = extensions.size();
	createInfo.ppEnabledExtensionNames = extensions.data();

	createInfo.enabledLayerCount = validationLayers.size();
	createInfo.ppEnabledLayerNames = validationLayers.data();

	VK_CHECK(vkCreateInstance(&createInfo, nullptr, &context->instance));
}

<<<<<<< HEAD

=======
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
void MasterRenderer::setupDebugCallback()
{
	VkDebugReportCallbackCreateInfoEXT createInfo =
		init::DebugReportCallbackCreateInfo(
			VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT);

	VK_CHECK(CreateDebugReportCallbackEXT(context->instance, &createInfo, nullptr, &context->callback));
}

void MasterRenderer::createSurface()
{
	VK_CHECK(glfwCreateWindowSurface(context->instance, context->display->getWindow(), nullptr, &context->surface));
}

void MasterRenderer::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(context->instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(context->instance, &deviceCount, devices.data());

	for (const auto& device : devices) {
		if (util::isDeviceSuitable(device)) {
			context->physicalDevice = device;
			break;
		}
	}

	if (context->physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}
}

void MasterRenderer::createLogicalDevice()
{
	context->indices = util::findQueueFamilies(context->physicalDevice);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<int> uniqueQueueFamilies = { context->indices.graphicsFamily, context->indices.presentFamily, context->indices.transferFamily };

	for (int queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo =
			init::DeviceQueueCreateInfo(
				queueFamily,
				1);
		queueCreateInfos.push_back(queueCreateInfo);
	}
	VkPhysicalDeviceFeatures deviceFeatures = {};
<<<<<<< HEAD
	deviceFeatures.fillModeNonSolid = true;
=======
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c

	VkDeviceCreateInfo createInfo =
		init::DeviceCreateInfo(
			queueCreateInfos.data(),
			queueCreateInfos.size(),
			&deviceFeatures);

	VK_CHECK(vkCreateDevice(context->physicalDevice, &createInfo, nullptr, &context->device));

	vkGetDeviceQueue(context->device, context->indices.graphicsFamily, 0, &context->graphicsQueue);
	vkGetDeviceQueue(context->device, context->indices.presentFamily, 0, &context->presentQueue);
	vkGetDeviceQueue(context->device, context->indices.transferFamily, 0, &context->transferQueue);
}

void MasterRenderer::createSwapChain()
{
	SwapChainSupportDetails swapChainSupport = util::querySwapChainSupport(context->physicalDevice);

	VkSurfaceFormatKHR surfaceFormat = util::chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = util::chooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = util::chooseSwapExtent(swapChainSupport.capabilities, context->display);

	context->swapChainImageFormat = surfaceFormat.format;
	context->swapChainExtent = extent;

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
	{
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}
	VkSwapchainCreateInfoKHR createInfo =
		init::SwapchainCreateInfo(
			context->surface,
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
	QueueFamilyIndices indices = util::findQueueFamilies(context->physicalDevice);
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
	VkSwapchainKHR oldSwapChain = context->swapChain;
	createInfo.oldSwapchain = oldSwapChain;

	VkSwapchainKHR newSwapChain;
	VK_CHECK(vkCreateSwapchainKHR(context->device, &createInfo, nullptr, &newSwapChain));
	*&context->swapChain = newSwapChain;

	vkGetSwapchainImagesKHR(context->device, context->swapChain, &imageCount, nullptr);
	context->swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(context->device, context->swapChain, &imageCount, context->swapChainImages.data());
}

void MasterRenderer::createRenderPass()
{
<<<<<<< HEAD
	VkAttachmentDescription colorAttachment =
=======
	VkAttachmentDescription attachment =
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
		init::AttachmentDescription(
			context->swapChainImageFormat,
			VK_SAMPLE_COUNT_1_BIT,
			VK_ATTACHMENT_LOAD_OP_CLEAR,
			VK_ATTACHMENT_STORE_OP_STORE,
			VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			VK_ATTACHMENT_STORE_OP_DONT_CARE,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

<<<<<<< HEAD
	VkAttachmentDescription depthAttachment =
		init::AttachmentDescription(
			util::findDepthFormat(),
			VK_SAMPLE_COUNT_1_BIT,
			VK_ATTACHMENT_LOAD_OP_CLEAR,
			VK_ATTACHMENT_STORE_OP_DONT_CARE,
			VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			VK_ATTACHMENT_STORE_OP_DONT_CARE,
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

=======
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
	VkAttachmentReference colorReference = {};
	colorReference.attachment = 0;
	colorReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

<<<<<<< HEAD
	VkAttachmentReference depthAttachmentRef = {};
	depthAttachmentRef.attachment = 1;
	depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

=======
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
	VkSubpassDescription subpassDescription =
		init::SubpassDescription(
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			1,
<<<<<<< HEAD
			&colorReference,
			1,
			&depthAttachmentRef);
=======
			&colorReference);
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;

	dependency.srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
	dependency.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;

	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;


<<<<<<< HEAD
	std::array<VkAttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };
	VkRenderPassCreateInfo createInfo =
		init::RenderPassCreateInfo(
			static_cast<uint32_t>(attachments.size()),
			attachments.data(),
			1,
			&subpassDescription,
			1,
=======
	VkRenderPassCreateInfo createInfo =
		init::RenderPassCreateInfo(
			1,
			&attachment,
			1,
			&subpassDescription,
			1,//static_cast<uint32_t>(dependencies.size()),
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
			&dependency);

	VK_CHECK(vkCreateRenderPass(context->device, &createInfo, nullptr, &context->renderPass));
}
void MasterRenderer::createImageViews()
{
	context->swapChainImageViews.resize(context->swapChainImages.size());
	for (uint32_t i = 0; i < context->swapChainImages.size(); i++)
	{
<<<<<<< HEAD
		util::createImageView(context->swapChainImages[i], context->swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, context->swapChainImageViews[i]);
=======
		util::createImageView(context->swapChainImages[i], context->swapChainImageFormat, context->swapChainImageViews[i]);
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
	}
}
void MasterRenderer::createFramebuffers()
{
	context->frameBuffers.resize(context->swapChainImages.size());

	for (uint32_t i = 0; i < context->swapChainImages.size(); i++)
	{
<<<<<<< HEAD
		std::array<VkImageView, 2> attachments = {
			context->swapChainImageViews[i],
			context->depthImageView
		};
		util::createImageView(context->swapChainImages[i], context->swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, context->swapChainImageViews[i]);
		VkFramebufferCreateInfo createInfo =
			init::FramebufferCreateInfo(
				context->renderPass,
				static_cast<uint32_t>(attachments.size()),
				attachments.data(),
=======
		VkImageView attachments[] = {
			context->swapChainImageViews[i]
		};
		util::createImageView(context->swapChainImages[i], context->swapChainImageFormat, context->swapChainImageViews[i]);
		VkFramebufferCreateInfo createInfo =
			init::FramebufferCreateInfo(
				context->renderPass,
				1,
				attachments,
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
				context->swapChainExtent.width,
				context->swapChainExtent.height,
				1);

		VK_CHECK(vkCreateFramebuffer(context->device, &createInfo, nullptr, &context->frameBuffers[i]))
	}
}

void MasterRenderer::createSemaphores()
{
	VkSemaphoreCreateInfo semaphoreInfo =
		init::SemaphoreCreateInfo();

	VK_CHECK(vkCreateSemaphore(context->device, &semaphoreInfo, nullptr, &context->imageAvailableSemaphore));
	VK_CHECK(vkCreateSemaphore(context->device, &semaphoreInfo, nullptr, &context->renderFinishedSemaphore));

	VkFenceCreateInfo fenceInfo =
		init::FenceCreateInfo(0);

	VK_CHECK(vkCreateFence(context->device, &fenceInfo, nullptr, &renderFence));
}

void MasterRenderer::createCommandPools()
{
	VkCommandPoolCreateInfo poolInfo =
		init::CommandPoolCreateInfo();
	poolInfo.queueFamilyIndex = context->indices.graphicsFamily;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	VK_CHECK(vkCreateCommandPool(context->device, &poolInfo, nullptr, &context->commandPool));

	poolInfo = init::CommandPoolCreateInfo();
	poolInfo.queueFamilyIndex = context->indices.transferFamily;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

	VK_CHECK(vkCreateCommandPool(context->device, &poolInfo, nullptr, &context->cmdTempPool));

	VkCommandBufferAllocateInfo allocInfo =
		init::CommandBufferAllocateInfo(context->commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, 1);

	vkAllocateCommandBuffers(context->device, &allocInfo, &primaryCommandBuffer);
}

<<<<<<< HEAD
void MasterRenderer::createDepthResources()
{

	VkFormat depthFormat = util::findDepthFormat();
	util::createImage(context->swapChainExtent.width, context->swapChainExtent.height,
		depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		context->depthImage, context->depthMemory);
	util::createImageView(context->depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, context->depthImageView);
	util::transitionImageLayout(context->depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

=======
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
void MasterRenderer::createCommandBuffer(VkFramebuffer& framebuffer)
{
	vkResetCommandBuffer(primaryCommandBuffer, 0);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	beginInfo.pInheritanceInfo = nullptr;

	vkBeginCommandBuffer(primaryCommandBuffer, &beginInfo);

	VkRenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = context->renderPass;
	renderPassInfo.framebuffer = framebuffer;
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = context->swapChainExtent;

<<<<<<< HEAD
	std::array<VkClearValue, 2> clearValues = {};
	clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
	clearValues[1].depthStencil = { 1.0f, 0 };

	renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	renderPassInfo.pClearValues = clearValues.data();


	vkCmdBeginRenderPass(primaryCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);


	//tileRenderer->render(primaryCommandBuffer);
	terrainRenderer->render(primaryCommandBuffer, camera);
=======
	VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;

	vkCmdBeginRenderPass(primaryCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	tileRenderer->render(primaryCommandBuffer);
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c

	vkCmdEndRenderPass(primaryCommandBuffer);

	VK_CHECK(vkEndCommandBuffer(primaryCommandBuffer));

}

void MasterRenderer::recreateSwapChain()
{
	vkDeviceWaitIdle(context->device);
<<<<<<< HEAD
	
	createSwapChain();
	createImageViews();
	createRenderPass();
	tileRenderer->createGraphicsPipeline();
	terrainRenderer->createGraphicsPipeline();
	createFramebuffers();
}

void MasterRenderer::windowResized(GLFWwindow * window, int width, int height)
{
	if (width == 0 || height == 0) return;
	MasterRenderer* renderer = reinterpret_cast<MasterRenderer*>(glfwGetWindowUserPointer(window));
	renderer->camera->updateAspectRatio(width / (float)height);
	renderer->context->display->setResolution(width, height);
	renderer->recreateSwapChain();
}

void MasterRenderer::keyPressed(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	MasterRenderer* r = reinterpret_cast<MasterRenderer*>(glfwGetWindowUserPointer(window));

	if (r->camera->firstperson)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			r->camera->keys.up = action != GLFW_RELEASE;
			break;
		case GLFW_KEY_S:
			r->camera->keys.down = action != GLFW_RELEASE;
			break;
		case GLFW_KEY_A:
			r->camera->keys.left = action != GLFW_RELEASE;
			break;
		case GLFW_KEY_D:
			r->camera->keys.right = action != GLFW_RELEASE;
			break;
		case GLFW_KEY_G:
			if(action == GLFW_PRESS)
			r->terrainRenderer->toggleWireframe();
		}
	}
}

void MasterRenderer::mousePressed(GLFWwindow * window, int button, int action, int mods)
{
	MasterRenderer* r = reinterpret_cast<MasterRenderer*>(glfwGetWindowUserPointer(window));
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_1:
		if (action == GLFW_PRESS) {
			leftMouseDown = true;
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			r->mousePos.x = (float)x;
			r->mousePos.y = (float)y;
		}
		else if (action == GLFW_RELEASE)
			leftMouseDown = false;
	case GLFW_MOUSE_BUTTON_2:
		if (action == GLFW_PRESS) {
			rightMouseDown = true;
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			r->mousePos.x = (float)x;
			r->mousePos.y = (float)y;
		}
		else if (action == GLFW_RELEASE)
			rightMouseDown = false;
		
	}
}

void MasterRenderer::mouseMove(GLFWwindow * window, double xPos, double yPos)
{
	MasterRenderer* r = reinterpret_cast<MasterRenderer*>(glfwGetWindowUserPointer(window));
	if (leftMouseDown)
	{
		float posx = static_cast<float>(xPos);
		float posy = static_cast<float>(yPos);
		r->zoom += (r->mousePos.y - posy) * .005f * r->zoomSpeed;
		r->camera->translate(glm::vec3(-0.0f, 0.0f, (r->mousePos.y - posy) * .005f * r->zoomSpeed));
		r->mousePos = glm::vec2(posx, posy);
		r->camera->viewChanged = true;
	}
	if (rightMouseDown)
	{
		float posx = static_cast<float>(xPos);
		float posy = static_cast<float>(yPos);
		r->rotation.x += (r->mousePos.y - posy) * 1.25f * r->rotationSpeed;
		r->rotation.y -= (r->mousePos.x - posx) * 1.25f * r->rotationSpeed;
		r->camera->rotate(glm::vec3((r->mousePos.y - posy) * r->camera->rotationSpeed, -(r->mousePos.x - posx) * r->camera->rotationSpeed, 0.0f));
		r->mousePos = glm::vec2(posx, posy);
		r->camera->viewChanged = true;
	}
=======

	createSwapChain();
	createFramebuffers();
	createRenderPass();
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
}

