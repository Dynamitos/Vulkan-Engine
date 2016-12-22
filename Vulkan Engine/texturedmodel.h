#pragma once
#include "rawmodel.h"
class TexturedModel :
	public RawModel
{
public:
	TexturedModel(MeshBuffer vertices, MeshBuffer indices);
	~TexturedModel();
	virtual void fillCommandBuffer(VkCommandBuffer& cmdBuffer);
protected:
};

