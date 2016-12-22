#include "terrain.h"
#include "utils.h"
#include "loader.h"


Terrain::Terrain(MeshBuffer vertices, MeshBuffer indices, int randSeed, double amplitude)
	:RawModel{ vertices, indices } {
	noise = new PerlinNoise(.5f, .5f, amplitude, 2, randSeed);
	context = Data::getInstance().getContext();
}


Terrain::~Terrain()
{
}

void Terrain::update()
{
	for (uint32_t x = 0; x < width; x++)
	{
		for (uint32_t y = 0; y < height; y++)
		{
			terrainData[x + y * width] = { static_cast<float>(noise->GetHeight(x, y)) };
			//std::cout << terrainData[x + y * width].displacement << std::endl;
		}
	}
	VkDeviceSize byteSize = sizeof(TerrainShader::TerrainOffset) * terrainData.size();
	void* data;
	vkMapMemory(context->device, displacement.stagMem, 0, displacement.size, 0, &data);
	memcpy(data, terrainData.data(), byteSize);
	vkUnmapMemory(context->device, displacement.stagMem);

	util::copyBuffer(displacement.stagBuf, displacement.buf, (size_t)byteSize);
}

Terrain * Terrain::generateTerrain(uint32_t width, uint32_t height, float scale, int randSeed, double amplitude)
{
	std::vector<TerrainShader::TerrainVertex> vertexData;
	vertexData.resize(width*height);
	for (uint32_t x = 0; x < width; x++)
	{
		for (uint32_t y = 0; y < height; y++)
		{
			vertexData[x + y * width] = TerrainShader::TerrainVertex( glm::vec3(x / static_cast<float>(width) * scale, 
																				0.f, 
																				y / static_cast<float>(height) * scale) );
		}
	}
	Loader& loader = Loader::getInstance();
	MeshBuffer vertexBuffer = loader.createVertexBuffer(vertexData.data(), vertexData.size(), sizeof(TerrainShader::TerrainVertex));
	std::vector<uint32_t> indexData;
	//0, 1,width
	//1, width, width + 1
	//i, i+1, i+width
	//i+1, i+width, i+width+1
	for (size_t j = 0; j < height - 1; j++)
	{
		for (uint32_t i = 0; i < width - 1; i++)
		{
			indexData.push_back(i + j * width);
			indexData.push_back(i + 1 + j * width);
			indexData.push_back(i + width + j * width);

			indexData.push_back(i + 1 + j * width);
			indexData.push_back(i + 1 + width + j * width);
			indexData.push_back(i + width + j * width);
		}
	}
	MeshBuffer indexBuffer = loader.createIndexBuffer(indexData.data(), indexData.size());
	Terrain* t = new Terrain(vertexBuffer, indexBuffer, randSeed, amplitude);
	t->terrainData.resize(width*height);
	t->displacement = loader.createStagedVertexBuffer(t->terrainData.data(), t->terrainData.size(), sizeof(TerrainShader::TerrainOffset));
	t->width = width;
	t->height = height;
	t->update();
	return t;
}

void Terrain::fillCommandBuffer(VkCommandBuffer & cmdBuffer)
{
	VkDeviceSize offsets[] = { 0, 0 };
	VkBuffer buffers[] = { vertices.buf, displacement.buf };
	vkCmdBindVertexBuffers(cmdBuffer, 0, 2, buffers, offsets);

	vkCmdBindIndexBuffer(cmdBuffer, indices.buf, 0, VK_INDEX_TYPE_UINT32);

}
