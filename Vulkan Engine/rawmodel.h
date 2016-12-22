#pragma once
#include <vulkan\vulkan.h>
struct MeshBuffer
{
	VkBuffer buf;
	VkDeviceMemory mem;
	uint32_t size;
};
struct StagedMeshBuffer : public MeshBuffer
{
	VkBuffer stagBuf;
	VkDeviceMemory stagMem;
};
class RawModel
{
public:
	RawModel(MeshBuffer vertices, MeshBuffer indices);
	~RawModel();
	uint32_t getIndicesCount();
	virtual void fillCommandBuffer(VkCommandBuffer& cmdBuffer);
protected:
	MeshBuffer vertices;
	MeshBuffer indices;
};

