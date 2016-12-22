#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in float height;

layout(location = 0) out vec4 out_Color;

void main(void)
{
	out_Color = vec4(height*2, height, 0.f, 1.f);
}