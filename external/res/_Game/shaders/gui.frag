#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 textureCoords;

layout(location = 0) out vec4 out_Color;

layout(binding = 1) uniform sampler2D guiTexture;

void main(void){

	out_Color = texture(guiTexture,textureCoords);

}