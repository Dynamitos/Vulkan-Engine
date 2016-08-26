#pragma once
#include "shader.h"
class TileShader : public Shader
{
public:
	TileShader(VkDevice device, VkExtent2D extent, const char* vertFile, const char* fragFile);
	~TileShader();
protected:
	const char* vertFile;
	const char* fragFile;
	void createPipeline();
	void createLayoutDescriptions();
	void createDescriptorSetLayout();

private:
	struct TileVertex
	{
		glm::vec3 pos;
		glm::vec2 texCoords;
	};
};

