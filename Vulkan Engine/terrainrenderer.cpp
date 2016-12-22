#include "terrainrenderer.h"
#include "loader.h"
#include "terrain.h"
#include "terrainshader.h"
#include "camera.h"
#include <glm\gtc\matrix_transform.inl>

TerrainRenderer::TerrainRenderer()
	:loader{ Loader::getInstance() } {
	context = Data::getInstance().getContext();
	shader = new TerrainShader("terrainVertex.spv", "terrainFragment.spv");
}

TerrainRenderer::~TerrainRenderer()
{
}

void TerrainRenderer::render(VkCommandBuffer& cmdBuffer, Camera* cam)
{
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;

	
	glm::mat4 model = glm::mat4();//glm::rotate(glm::mat4(), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	
	if (cam->viewChanged) {

		shader->loadViewMatrix(cam->matrices.view);
		shader->loadProjection(cam->matrices.perspective);
	}
	shader->loadModelMatrix(model);

	shader->bindPipeline(cmdBuffer);

	terrain->fillCommandBuffer(cmdBuffer);

	shader->bindDescriptorSets(cmdBuffer);

	vkCmdDrawIndexed(cmdBuffer, terrain->getIndicesCount(), 1, 0, 0, 0);
}

void TerrainRenderer::createDescriptorSetLayout()
{
	shader->createDescriptorSetLayout();
}

void TerrainRenderer::createGraphicsPipeline()
{
	shader->createPipeline();
}

void TerrainRenderer::createShaderData()
{
	srand(time(NULL));
	terrain = Terrain::generateTerrain(1000, 1000, 10, rand(), 1.f);
	shader->createUniforms();
}

void TerrainRenderer::createDescriptorPool()
{
	shader->createDescriptorPool();
}

void TerrainRenderer::createDescriptorSet()
{
	shader->createDescriptorSet();
}

void TerrainRenderer::toggleWireframe()
{
	shader->bWireframe = !shader->bWireframe;
}

