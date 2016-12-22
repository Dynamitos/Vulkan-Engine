#pragma once
#include <vector>
#include <vulkan\vulkan.h>
#include <glm\glm.hpp>
#include "utils.h"


class Shader
{
public:
	Shader();
	~Shader();
	virtual void createPipeline();
	virtual void createLayoutDescriptions();
	virtual void createDescriptorSet();
protected:
	void copyUniformBuffer(UniformBuffer* buffer, void* data, size_t length);

	VulkanContext* context;
	VkPipeline pipeline;
	VkPipelineLayout pipelineLayout;
	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorSet descriptorSet;
	VkPipelineVertexInputStateCreateInfo inputState;
	std::vector<VkVertexInputAttributeDescription> attribDesc;
	std::vector<VkVertexInputBindingDescription> binding;
};