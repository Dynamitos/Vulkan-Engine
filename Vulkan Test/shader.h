#ifndef SHADER_H
#define SHADER_H

#include <vulkan\vulkan.h>

#include "datastructures.h"

class Shader
{
public:
	Shader(VkDevice device, const char* vertexShader, const char* fragmentShader);
	~Shader();
protected:
	virtual void createVertexAttributes();
	virtual void createDescriptorPool();
	virtual void createUniformBuffers();
	VkDevice device;
	VkPipelineShaderStageCreateInfo loadShader(std::string fileName, VkShaderStageFlagBits stage);
	void createBuffer(VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize size, void* data, VkBuffer* buffer, VkDeviceMemory memory);
	VkVertexInputBindingDescription bindingDescription;
	std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
	VkPipelineVertexInputStateCreateInfo inputState;
	std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
	std::vector<VkShaderModule> shaderModules;
	VkDescriptorPool descriptorPool;
	VkPipeline pipeline;
	void createPipelineRequirements();
};

#endif