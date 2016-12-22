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
<<<<<<< HEAD
	StagedMeshBuffer createStagedVertexBuffer(void* vertices, VkDeviceSize vertexCount, size_t vertexSize);
=======
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
	static Loader& getInstance();
private:
	VulkanContext* context;
	Loader(void);
	Loader(const Loader& src);
	static std::unique_ptr<Loader> m_instance;
	static std::once_flag m_onceFlag;
};

