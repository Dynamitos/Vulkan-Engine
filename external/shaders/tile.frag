#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 texCoords_FS_in;

layout(location = 0) out vec4 out_Color;

layout(binding = 3) uniform sampler2D terrainTex;
layout(binding = 4) uniform sampler2D itemTex;

void main(void)
{
	vec4 terrainColor = texture(terrainTex, texCoords_FS_in);
	vec4 itemColor = texture(itemTex, texCoords_FS_in);
	out_Color = terrainColor;
}