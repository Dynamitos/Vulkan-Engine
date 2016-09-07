#pragma once
#include "utils.h"
#include "tilerenderer.h"
class MasterRenderer
{
public:
	MasterRenderer();
	~MasterRenderer();
private:
	void render();
	void initInstance();
	void setupDebugCallback();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createRenderPass();
	void createImageViews();
	void createFramebuffers();
	void createSemaphores();
	void createCommandPools();
	void createCommandBuffer(VkFramebuffer& framebuffer);
	void recreateSwapChain();
	VulkanContext* context;
	VkCommandBuffer primaryCommandBuffer;//submitted for execution
	VkFence renderFence;
	//Holds all sub-renderers
	TileRenderer* tileRenderer;

};