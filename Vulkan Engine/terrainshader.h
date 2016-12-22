#pragma once
#include "shader.h"
class TerrainShader : public Shader
{
public:
	TerrainShader(const char* vertFile, const char* fragFile);
	virtual ~TerrainShader();
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
	struct TerrainVertex
	{
		glm::vec3 pos;
		TerrainVertex(glm::vec3 pos)
			:pos{ pos } {}
		TerrainVertex()
			:pos{ glm::vec3() } {};
	};
	struct TerrainOffset
	{
		float displacement;
		TerrainOffset(float displacement)
			:displacement{ displacement } {}
		TerrainOffset()
			:displacement{ 0 } {}
	};
	bool bWireframe;
protected:
	const char* vertFile;
	const char* fragFile;
	VkPipeline wireFrame;
private:
	VkDescriptorPool descriptorPool;
	UniformBuffer* modelBuffer;
	UniformBuffer* viewBuffer;
	UniformBuffer* projBuffer;
};

