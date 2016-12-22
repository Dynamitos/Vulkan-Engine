#pragma once
#include <vulkan\vulkan.h>
struct MeshBuffer
{
	VkBuffer buf;
	VkDeviceMemory mem;
	uint32_t size;
};
<<<<<<< HEAD
struct StagedMeshBuffer : public MeshBuffer
{
	VkBuffer stagBuf;
	VkDeviceMemory stagMem;
};
=======
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
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

