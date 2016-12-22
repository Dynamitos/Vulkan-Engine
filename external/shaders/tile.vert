#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords_VS_in;

layout(location = 0) out vec2 texCoords_FS_in;

layout(binding = 0) uniform ModelStruct{ mat4 matrix; } model;
layout(binding = 1) uniform ViewStruct{ mat4 matrix; } view;
layout(binding = 2) uniform ProjStruct{ mat4 matrix; } proj;

void main()
{
	gl_Position = proj.matrix * view.matrix * model.matrix * vec4(position, 1);
	texCoords_FS_in = texCoords_VS_in;
}