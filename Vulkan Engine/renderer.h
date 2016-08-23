#pragma once
#include <vulkan\vulkan.h>
#include <vector>
class Renderer
{
public:
	Renderer();
	~Renderer();
protected:
	virtual void createCommandBuffers(VkCommandBufferInheritanceInfo inheritance);
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
};