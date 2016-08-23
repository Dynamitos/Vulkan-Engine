#pragma once
#include "shader.h"
#define VERTEX_BUFFER_BIND_ID 0

struct EntityVertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	glm::vec3 color;
	glm::vec4 weights;
	glm::ivec4 IDs;
};

class EntityShader :
	public Shader
{
public:
	EntityShader::EntityShader(VkDevice device, const char* vertFile, const char* fragFile);
	virtual ~EntityShader();
private:
	void createVertexAttributes();
	void createDescriptorPool();
	void createUniformBuffers();
};

