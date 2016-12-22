#pragma once
#include "rawmodel.h"
#include "utils.h"
#include "terrainshader.h"
#include "perlinnoise.h"

class Terrain : public RawModel
{
public:
	virtual ~Terrain();
	void update();
	static Terrain* generateTerrain(uint32_t width, uint32_t height, float scale, int randSeed, double amplitude);
	virtual void fillCommandBuffer(VkCommandBuffer& cmdBuffer);
private:
	Terrain(MeshBuffer vertices, MeshBuffer indices, int randSeed, double amplitude);
	std::vector<TerrainShader::TerrainOffset> terrainData;
	StagedMeshBuffer displacement;
	PerlinNoise* noise;
	uint32_t width, height;
	VulkanContext* context;
};

