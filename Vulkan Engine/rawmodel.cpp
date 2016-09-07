#include "rawmodel.h"

RawModel::RawModel(MeshBuffer vertices, MeshBuffer indices)
{
	this->vertices = vertices;
	this->indices = indices;
}

RawModel::~RawModel()
{
}

uint32_t RawModel::getIndicesCount()
{
	return indices.size;
}

void RawModel::fillCommandBuffer(VkCommandBuffer& cmdBuffer) {
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(cmdBuffer, 0, 1, &vertices.buf, offsets);

	vkCmdBindIndexBuffer(cmdBuffer, indices.buf, 0, VK_INDEX_TYPE_UINT32);
}
