#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 position;
layout(location = 1) in float displacement;

layout(location = 0) out float height;

layout(set = 0, binding = 0) uniform ModelStruct{ mat4 matrix; } model;
layout(set = 0, binding = 1) uniform ViewStruct{ mat4 matrix; } view;
layout(set = 0, binding = 2) uniform ProjStruct{ mat4 matrix; } proj;

void main()
{
	
	gl_Position = proj.matrix * view.matrix * model.matrix * vec4(position.x, position.y+displacement, position.z, 1);
	height = displacement;
}