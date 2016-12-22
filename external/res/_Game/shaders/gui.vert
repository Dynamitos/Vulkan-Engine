#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 position;

layout(location = 0) out vec2 textureCoords;

layout(binding = 0) uniform ModelStruct{ mat4 matrix; } model;

void main(void){

	gl_Position = model.matrix * vec4(position, 0.0, 1.0);
	textureCoords = vec2((position.x+1.0)/2.0, 1 - (position.y+1.0)/2.0);
}