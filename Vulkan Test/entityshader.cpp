#include "entityshader.h"



EntityShader::EntityShader(VkDevice device, const char* vertFile, const char* fragFile)
	:Shader{ device, vertFile, fragFile } {
}


EntityShader::~EntityShader()
{
}

void EntityShader::createVertexAttributes()
{
	bindingDescription =
		vkTools::initializers::vertexInputBindingDescription(
			VERTEX_BUFFER_BIND_ID,
			sizeof(EntityVertex),
			VK_VERTEX_INPUT_RATE_VERTEX);

	attributeDescriptions.resize(6);
	// Location 0 : Position
	attributeDescriptions[0] =
		vkTools::initializers::vertexInputAttributeDescription(
			VERTEX_BUFFER_BIND_ID,
			0,
			VK_FORMAT_R32G32B32_SFLOAT,
			0);
	// Location 1 : Normal
	attributeDescriptions[1] =
		vkTools::initializers::vertexInputAttributeDescription(
			VERTEX_BUFFER_BIND_ID,
			1,
			VK_FORMAT_R32G32B32_SFLOAT,
			sizeof(float) * 3);
	// Location 2 : Texture coordinates
	attributeDescriptions[2] =
		vkTools::initializers::vertexInputAttributeDescription(
			VERTEX_BUFFER_BIND_ID,
			2,
			VK_FORMAT_R32G32_SFLOAT,
			sizeof(float) * 6);
	// Location 3 : Color
	attributeDescriptions[3] =
		vkTools::initializers::vertexInputAttributeDescription(
			VERTEX_BUFFER_BIND_ID,
			3,
			VK_FORMAT_R32G32B32_SFLOAT,
			sizeof(float) * 8);
	// Location 4 : Bone weights
	attributeDescriptions[4] =
		vkTools::initializers::vertexInputAttributeDescription(
			VERTEX_BUFFER_BIND_ID,
			4,
			VK_FORMAT_R32G32B32A32_SFLOAT,
			sizeof(float) * 11);
	// Location 5 : Bone IDs
	attributeDescriptions[5] =
		vkTools::initializers::vertexInputAttributeDescription(
			VERTEX_BUFFER_BIND_ID,
			5,
			VK_FORMAT_R32G32B32A32_SINT,
			sizeof(float) * 15);

	inputState = vkTools::initializers::pipelineVertexInputStateCreateInfo();
	inputState.vertexAttributeDescriptionCount = attributeDescriptions.size();
	inputState.pVertexAttributeDescriptions = attributeDescriptions.data();
	inputState.pVertexBindingDescriptions = &bindingDescription;
	inputState.vertexBindingDescriptionCount = 1;
}

void EntityShader::createDescriptorPool()
{
}

void EntityShader::createUniformBuffers()
{
	//createBuffer
}
