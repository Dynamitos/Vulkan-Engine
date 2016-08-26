#pragma once
#include <vector>
#include <vulkan\vulkan.h>
#include <glm\glm.hpp>
#include "utils.h"
class Shader
{
public:
	Shader(VkDevice device, VkExtent2D extent);
	~Shader();
protected:
	virtual void createPipeline();
	virtual void createLayoutDescriptions();
	virtual void createDescriptorSet();
	VkPipeline pipeline;
	VkPipelineLayout pipelineLayout;
	VkPipelineVertexInputStateCreateInfo inputState;
	std::vector<VkVertexInputAttributeDescription> attribDesc;
	std::vector<VkVertexInputBindingDescription> binding;
	VkDevice device;
	VkExtent2D extent;
};