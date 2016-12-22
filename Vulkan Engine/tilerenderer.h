#pragma once
#include <glm/gtc/matrix_transform.inl>
#include <glm\glm.hpp>
#include "tileshader.h"
#include "utils.h"
#include "loader.h"

static std::vector<TileShader::TileVertex> vertices = {
	{ {-0.5f, -0.5f, 0.0f}, { 0.0f, 0.0f } },
	{ { 0.5f, -0.5f, 0.0f}, { 1.0f, 0.0f } },
	{ {-0.5f,  0.5f, 0.0f}, { 0.0f, 1.0f } },
	{ { 0.5f,  0.5f, 0.0f}, { 1.0f, 1.0f } }
};
static uint32_t indices[] = {
	0, 1, 2,
	2, 1, 3
};
class TileRenderer
{
public:
	TileRenderer();
	~TileRenderer();
	void render(VkCommandBuffer& cmdBuffer);
	void createDescriptorSetLayout();
	void createGraphicsPipeline();
	void createShaderData();
	void createDescriptorPool();
	void createDescriptorSet();
private:
	Loader& loader;
	TexturedModel* defaultModel;
	VulkanContext* context;
	TileShader* tileShader;
	
};