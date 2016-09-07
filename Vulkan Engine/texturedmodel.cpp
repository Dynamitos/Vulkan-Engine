#include "texturedmodel.h"



TexturedModel::TexturedModel(MeshBuffer vertices, MeshBuffer indices)
	:RawModel(vertices, indices) {
}


TexturedModel::~TexturedModel()
{
}

void TexturedModel::fillCommandBuffer(VkCommandBuffer & cmdBuffer)
{
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(cmdBuffer, 0, 1, &vertices.buf, offsets);
	
	vkCmdBindIndexBuffer(cmdBuffer, indices.buf, 0, VK_INDEX_TYPE_UINT32);
}
