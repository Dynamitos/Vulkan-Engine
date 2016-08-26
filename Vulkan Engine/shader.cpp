#include "shader.h"

Shader::Shader(VkDevice device, VkExtent2D extent)
	:device{ device }{
	this->extent = extent;
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
