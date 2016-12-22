#include "shader.h"

Shader::Shader(){
}
Shader::~Shader()
{

}

void Shader::createPipeline()
{
}

void Shader::createLayoutDescriptions()
{
}

void Shader::createDescriptorSet()
{
}

void Shader::copyUniformBuffer(UniformBuffer* buffer, void * data, size_t length)
{
	void* destination = nullptr;
	vkMapMemory(context->device, buffer->stagingBufferMemory, 0, buffer->bufferSize, 0, &destination);
	memcpy(destination, data, 16 * sizeof(float));
	vkUnmapMemory(context->device, buffer->stagingBufferMemory);

	util::copyBuffer(buffer->stagingBuffer, buffer->uniformBuffer, buffer->bufferSize);
}
