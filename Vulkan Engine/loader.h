#pragma once
#include <memory>
#include <mutex>
#include "utils.h"
#include "texturedmodel.h"
class Loader
{
public:
	virtual ~Loader();
	MeshBuffer createIndexBuffer(uint32_t* indices, VkDeviceSize indexCount);
	MeshBuffer createVertexBuffer(void* vertices, VkDeviceSize vertexCount, size_t vertexSize);
	StagedMeshBuffer createStagedVertexBuffer(void* vertices, VkDeviceSize vertexCount, size_t vertexSize);
	static Loader& getInstance();
private:
	VulkanContext* context;
	Loader(void);
	Loader(const Loader& src);
	static std::unique_ptr<Loader> m_instance;
	static std::once_flag m_onceFlag;
};

