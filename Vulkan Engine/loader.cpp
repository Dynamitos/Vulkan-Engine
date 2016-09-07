#include "loader.h"



Loader::Loader()
{
	context = Data::getInstance().getContext();
}


Loader::~Loader()
{
}
MeshBuffer Loader::createIndexBuffer(uint32_t* indices, VkDeviceSize indexCount)
{
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingMemory;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkDeviceSize byteSize = indexCount*sizeof(uint32_t);
	util::createBuffer(byteSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingMemory);

	void* data;
	vkMapMemory(context->device, stagingMemory, 0, byteSize, 0, &data);
	memcpy(data, indices, (size_t)byteSize);
	vkUnmapMemory(context->device, stagingMemory);

	util::createBuffer(byteSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

	util::copyBuffer(stagingBuffer, vertexBuffer, byteSize);
	MeshBuffer buffer;
	buffer.buf = vertexBuffer;
	buffer.mem = vertexBufferMemory;
	buffer.size = indexCount;
	return buffer;
}
MeshBuffer Loader::createVertexBuffer(void* vertices, VkDeviceSize deviceSize, size_t vertexSize)
{
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingMemory;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkDeviceSize byteSize = deviceSize*vertexSize;
	util::createBuffer(byteSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingMemory);
	
	void* data;
	vkMapMemory(context->device, stagingMemory, 0, byteSize, 0, &data);
	memcpy(data, vertices, (size_t)byteSize);
	vkUnmapMemory(context->device, stagingMemory);

	util::createBuffer(byteSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

	util::copyBuffer(stagingBuffer, vertexBuffer, byteSize);
	MeshBuffer buffer;
	buffer.buf = vertexBuffer;
	buffer.mem = vertexBufferMemory;
	buffer.size = deviceSize;
	return buffer;
}
std::unique_ptr<Loader> Loader::m_instance;
std::once_flag Loader::m_onceFlag;

Loader & Loader::getInstance()
{
	std::call_once(m_onceFlag,
		[] {
		m_instance.reset(new Loader);
	});
	return *m_instance.get();
}
