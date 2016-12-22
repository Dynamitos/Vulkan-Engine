#include "tilerenderer.h"

TileRenderer::TileRenderer()
	:tileShader{ new TileShader("tileVertex.spv", "tileFragment.spv") },
	loader{ Loader::getInstance() } {
	context = Data::getInstance().getContext();
}


TileRenderer::~TileRenderer()
{
}

void TileRenderer::render(VkCommandBuffer& cmdBuffer)
{
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;

	glm::mat4 model = glm::rotate(glm::mat4(), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), context->swapChainExtent.width / (float)context->swapChainExtent.height, 0.1f, 10.0f);

	tileShader->loadModelMatrix(model);
	tileShader->loadViewMatrix(view);
	tileShader->loadProjection(proj);

	tileShader->bindPipeline(cmdBuffer);

	defaultModel->fillCommandBuffer(cmdBuffer);

	tileShader->bindDescriptorSets(cmdBuffer);

	vkCmdDrawIndexed(cmdBuffer, defaultModel->getIndicesCount(), 1, 0, 0, 0);
}

void TileRenderer::createDescriptorSetLayout()
{
	tileShader->createDescriptorSetLayout();
}

void TileRenderer::createGraphicsPipeline()
{
	tileShader->createPipeline();
}

void TileRenderer::createShaderData()
{
	defaultModel = new TexturedModel(loader.createVertexBuffer(vertices.data(), 4, sizeof(TileShader::TileVertex)),
		loader.createIndexBuffer(indices, 6));
	tileShader->createUniforms();
}

void TileRenderer::createDescriptorPool()
{
	tileShader->createDescriptorPool();
}

void TileRenderer::createDescriptorSet()
{
	tileShader->createDescriptorSet();
}


