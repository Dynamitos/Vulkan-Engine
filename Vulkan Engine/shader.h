#pragma once
#include <vector>
#include <vulkan\vulkan.h>
class Shader
{
public:
	Shader();
	~Shader();
protected:
	virtual void setupUniformBuffers();
	virtual void setupVertexLayout();
	virtual void createPipeline();
	VkPipeline pipeline;
	VkPipelineLayout pipelineLayout;
	VkPipelineVertexInputStateCreateInfo inputState;
	std::vector<VkVertexInputAttributeDescription> attribDesc;
	std::vector<VkVertexInputBindingDescription> binding;
};