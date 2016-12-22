#pragma once
#include "shader.h"
class TileShader : public Shader
{
public:
	TileShader(const char* vertFile, const char* fragFile);
	~TileShader();
	void bindPipeline(VkCommandBuffer& cmdBuffer);
	void bindDescriptorSets(VkCommandBuffer& cmdBuffer);
	void createPipeline();
	void createUniforms();
	void createLayoutDescriptions();
	void createDescriptorSetLayout();
	void createDescriptorSet();
	void createDescriptorPool();
	void loadProjection(glm::mat4 projectionMatrix);
	void loadViewMatrix(glm::mat4 viewMatrix);
	void loadModelMatrix(glm::mat4 modelMatrix);
	struct TileVertex
	{
		glm::vec3 pos;
		glm::vec2 texCoords;
		TileVertex(glm::vec3 pos, glm::vec2 texCoords) 
			:pos{ pos }, texCoords{ texCoords } {}
	};
protected:
	const char* vertFile;
	const char* fragFile;
private:
	VkDescriptorPool descriptorPool;
	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 model;
	UniformBuffer* modelBuffer;
	UniformBuffer* viewBuffer;
	UniformBuffer* projBuffer;
	UniformTexture* terrainTex;
	UniformTexture* itemTex;
	
};

