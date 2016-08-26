#include "tileshader.h"

TileShader::TileShader(VkDevice device, VkExtent2D extent2D, const char* vertFile, const char* fragFile)
	:Shader{ device, extent2D }, vertFile{ vertFile }, fragFile{ fragFile } {
}


TileShader::~TileShader()
{
}

void TileShader::createPipeline()
{
	auto vertModule = util::loadShader(device, vertFile, VK_SHADER_STAGE_VERTEX_BIT);
	auto fragModule = util::loadShader(device, fragFile, VK_SHADER_STAGE_FRAGMENT_BIT);

	VkPipelineShaderStageCreateInfo vertShaderStageInfo =
		init::PipelineShaderStageCreateInfo(
			VK_SHADER_STAGE_VERTEX_BIT,
			vertModule,
			"main");

	VkPipelineShaderStageCreateInfo fragShaderStageInfo =
		init::PipelineShaderStageCreateInfo(
			VK_SHADER_STAGE_FRAGMENT_BIT,
			fragModule,
			"main");

	VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	createLayoutDescriptions();
	

	VkPipelineVertexInputStateCreateInfo vertexInputInfo =
		init::PipelineVertexInputStateCreateInfo();
	vertexInputInfo.vertexBindingDescriptionCount = binding.size();
	vertexInputInfo.pVertexBindingDescriptions = binding.data();
	vertexInputInfo.vertexAttributeDescriptionCount = attribDesc.size();
	vertexInputInfo.pVertexAttributeDescriptions = attribDesc.data();

	VkPipelineInputAssemblyStateCreateInfo inputAssemby =
		init::PipelineInputAssemblyStateCreateInfo(
			VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
			0,
			VK_FALSE);

	VkViewport viewPort =
		init::Viewport(
			extent.width,
			extent.height,
			0.0f,
			1.0f);

	VkRect2D scissor = {};
	scissor.offset = { 0, 0 };
	scissor.extent = extent;

	VkPipelineViewportStateCreateInfo viewportState =
		init::PipelineViewportStateCreateInfo(
			1,
			1,
			0);
	viewportState.pViewports = &viewPort;
	viewportState.pScissors = &scissor;

	VkPipelineRasterizationStateCreateInfo rasterizer =
		init::PipelineRasterizationStateCreateInfo(
			VK_POLYGON_MODE_FILL,
			VK_CULL_MODE_NONE,
			VK_FRONT_FACE_COUNTER_CLOCKWISE,
			0);
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.lineWidth = 1.0f;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling =
		init::PipelineMultisampleStateCreateInfo(
			VK_SAMPLE_COUNT_1_BIT,
			0);

	VkPipelineColorBlendAttachmentState colorBlendAttachment =
		init::PipelineColorBlendAttachmentState(
			VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
			VK_FALSE);

	VkPipelineColorBlendStateCreateInfo colorBlending =
		init::PipelineColorBlendStateCreateInfo(
			1,
			&colorBlendAttachment);
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	createDescriptorSetLayout();
	//VkDescriptorSetLayout setLayouts[] = { descriptorSetLayout };
}

void TileShader::createLayoutDescriptions()
{
	binding.resize(1);
	binding[0] =
		init::VertexInputBindingDescription(
			0,
			sizeof(TileVertex),
			VK_VERTEX_INPUT_RATE_VERTEX);

	attribDesc.resize(2);
	attribDesc[0].binding = 0;
	attribDesc[0].location = 0;
	attribDesc[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	attribDesc[0].offset = offsetof(TileVertex, pos);

	attribDesc[1].binding = 0;
	attribDesc[1].location = 1;
	attribDesc[1].format = VK_FORMAT_R32G32_SFLOAT;
	attribDesc[1].offset = offsetof(TileVertex, texCoords);

}

void TileShader::createDescriptorSetLayout()
{
	VkDescriptorSetLayoutBinding transBinding =
		init::DescriptorSetLayoutBinding(
			VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			VK_SHADER_STAGE_VERTEX_BIT,
			0,
			1);

	VkDescriptorSetLayoutBinding viewBinding =
		init::DescriptorSetLayoutBinding(
			VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			VK_SHADER_STAGE_VERTEX_BIT,
			1,
			1);

	VkDescriptorSetLayoutBinding projBinding =
		init::DescriptorSetLayoutBinding(
			VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			VK_SHADER_STAGE_VERTEX_BIT,
			2,
			1);


}
