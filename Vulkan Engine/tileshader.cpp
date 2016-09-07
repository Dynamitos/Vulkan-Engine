#include "tileshader.h"

TileShader::TileShader(const char* vertFile, const char* fragFile)
	:vertFile{ vertFile }, fragFile{ fragFile } {
	context = Data::getInstance().getContext();

}


TileShader::~TileShader()
{
}

void TileShader::bindPipeline(VkCommandBuffer & cmdBuffer)
{
	vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
}

void TileShader::bindDescriptorSets(VkCommandBuffer & cmdBuffer)
{
	vkCmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
}

void TileShader::createPipeline()
{
	auto vertModule = util::loadShader(vertFile);
	auto fragModule = util::loadShader(fragFile);

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
			context->swapChainExtent.width,
			context->swapChainExtent.height,
			0.0f,
			1.0f);

	VkRect2D scissor = {};
	scissor.offset = { 0, 0 };
	scissor.extent = context->swapChainExtent;

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

	VkDescriptorSetLayout setLayouts[] = { descriptorSetLayout };
	VkPipelineLayoutCreateInfo pipelineLayoutInfo =
		init::PipelineLayoutCreateInfo(
			setLayouts,
			1);

	VK_CHECK(vkCreatePipelineLayout(context->device, &pipelineLayoutInfo, nullptr, &pipelineLayout));

	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssemby;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.layout = pipelineLayout;
	pipelineInfo.renderPass = context->renderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	VK_CHECK(vkCreateGraphicsPipelines(context->device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline));
}

void TileShader::createUniforms()
{	
	terrainTex = new UniformTexture("C:\\Users\\Dynamitos5\\Documents\\Schule\\POS\\Vulkan Test\\external\\textures\\ic_launcher.png");
	itemTex = new UniformTexture("C:\\Users\\Dynamitos5\\Documents\\Schule\\POS\\Vulkan Test\\external\\textures\\ic_launcher.png");
	modelBuffer = new UniformBuffer((uint32_t)sizeof(glm::mat4));
	viewBuffer = new UniformBuffer((uint32_t)sizeof(glm::mat4));
	projBuffer = new UniformBuffer((uint32_t)sizeof(glm::mat4));
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

	VkDescriptorSetLayoutBinding terrainBinding =
		init::DescriptorSetLayoutBinding(
			VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			VK_SHADER_STAGE_FRAGMENT_BIT,
			3,
			1);

	VkDescriptorSetLayoutBinding itemBinding =
		init::DescriptorSetLayoutBinding(
			VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			VK_SHADER_STAGE_FRAGMENT_BIT,
			4,
			1);

	std::array<VkDescriptorSetLayoutBinding, 5> bindings = { transBinding, viewBinding, projBinding, terrainBinding, itemBinding };
	VkDescriptorSetLayoutCreateInfo layoutInfo =
		init::DescriptorSetLayoutCreateInfo(
			bindings.data(),
			bindings.size());

	VK_CHECK(vkCreateDescriptorSetLayout(context->device, &layoutInfo, nullptr, &descriptorSetLayout));
}

void TileShader::createDescriptorSet()
{

	VkDescriptorSetLayout layout[] = { descriptorSetLayout };
	VkDescriptorSetAllocateInfo allocInfo =
		init::DescriptorSetAllocateInfo(
			descriptorPool,
			layout,
			1);

	VK_CHECK(vkAllocateDescriptorSets(context->device, &allocInfo, &descriptorSet));

	VkDescriptorBufferInfo modelInfo =
		init::DescriptorBufferInfo(
			modelBuffer->uniformBuffer,
			0,
			modelBuffer->bufferSize);

	VkDescriptorBufferInfo viewInfo =
		init::DescriptorBufferInfo(
			viewBuffer->uniformBuffer,
			0,
			viewBuffer->bufferSize);

	VkDescriptorBufferInfo projInfo =
		init::DescriptorBufferInfo(
			projBuffer->uniformBuffer,
			0,
			projBuffer->bufferSize);

	VkDescriptorImageInfo terrainInfo =
		init::DescriptorImageInfo(
			terrainTex->sampler,
			terrainTex->imageView,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	VkDescriptorImageInfo itemInfo =
		init::DescriptorImageInfo(
			itemTex->sampler,
			itemTex->imageView,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	VkWriteDescriptorSet modelWrite =
		init::WriteDescriptorSet(
			descriptorSet,
			VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			0,
			&modelInfo);

	VkWriteDescriptorSet viewWrite =
		init::WriteDescriptorSet(
			descriptorSet,
			VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			1,
			&viewInfo);

	VkWriteDescriptorSet projWrite =
		init::WriteDescriptorSet(
			descriptorSet,
			VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			2,
			&projInfo);

	VkWriteDescriptorSet terrainWrite =
		init::WriteDescriptorSet(
			descriptorSet,
			VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			3,
			&terrainInfo);

	VkWriteDescriptorSet itemWrite =
		init::WriteDescriptorSet(
			descriptorSet,
			VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			4,
			&itemInfo);

	std::array<VkWriteDescriptorSet, 5> descriptorWrites = { modelWrite, viewWrite, projWrite, terrainWrite, itemWrite };

	vkUpdateDescriptorSets(context->device, descriptorWrites.size(), descriptorWrites.data(), 0, nullptr);
}

void TileShader::createDescriptorPool()
{
	std::array<VkDescriptorPoolSize, 5> poolSizes = {};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = 1;
	poolSizes[1].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[1].descriptorCount = 1;
	poolSizes[2].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[2].descriptorCount = 1;
	poolSizes[3].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[3].descriptorCount = 1;
	poolSizes[4].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[4].descriptorCount = 1;

	VkDescriptorPoolCreateInfo poolInfo =
		init::DescriptorPoolCreateInfo(
			(uint32_t)poolSizes.size(),
			poolSizes.data(),
			1);

	VK_CHECK(vkCreateDescriptorPool(context->device, &poolInfo, nullptr, &descriptorPool));

}

void TileShader::loadProjection(glm::mat4 projectionMatrix)
{
	copyUniformBuffer(projBuffer, &projectionMatrix[0], 16 * sizeof(float));
}

void TileShader::loadViewMatrix(glm::mat4 viewMatrix)
{
	copyUniformBuffer(viewBuffer, &viewMatrix[0], 16 * sizeof(float));
}
void TileShader::loadModelMatrix(glm::mat4 modelMatrix)
{
	copyUniformBuffer(modelBuffer, &modelMatrix[0], 16 * sizeof(float));
}
