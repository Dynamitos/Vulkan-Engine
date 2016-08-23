#pragma once
#include "utils.h"
#include "renderer.h"
class MasterRenderer
{
public:
	MasterRenderer();
	~MasterRenderer();
private:
	void initInstance();
	void setupDebugCallback();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createRenderPass();
	void createFramebuffers();
	Display* display;
	VkInstance instance;
	VkDebugReportCallbackEXT callback;
	VkSurfaceKHR surface;
	VkPhysicalDevice physicalDevice;
	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkQueue transferQueue;
	VkSwapchainKHR swapChain;
	VkExtent2D swapChainExtent;
	VkFormat swapChainImageFormat;
	VkRenderPass renderPass;
	std::vector<VkImage> swapChainImages;
	std::vector<VkFramebuffer> frameBuffers;

	//Holds all sub-renderers
	std::vector<Renderer> renderers;
};