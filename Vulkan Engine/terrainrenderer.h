#pragma once
#include "utils.h"

class Terrain;
class Loader;
class TerrainShader;
class Camera;

class TerrainRenderer
{
public:
	TerrainRenderer();
	virtual ~TerrainRenderer();
	void render(VkCommandBuffer& cmdBuffer, Camera* cam);
	void createDescriptorSetLayout();
	void createGraphicsPipeline();
	void createShaderData();
	void createDescriptorPool();
	void createDescriptorSet();
	void toggleWireframe();
private:
	Loader& loader;
	VulkanContext* context;
	Terrain* terrain;
	TerrainShader* shader;
};

