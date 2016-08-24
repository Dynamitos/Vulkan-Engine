#pragma once
#include <vulkan\vulkan.h>
struct MeshBuffer
{
	VkBuffer buf;
	VkDeviceMemory mem;
	uint32_t size;
};
class RawModel
{
public:
	RawModel(MeshBuffer vertices, MeshBuffer indices);
	~RawModel();
private:
	VkBuffer vertices;
	VkBuffer indices;
	uint32_t numIndices;
};

