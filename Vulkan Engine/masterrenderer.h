#pragma once
#include "utils.h"
#include "tilerenderer.h"
<<<<<<< HEAD
#include "terrainrenderer.h"
#include "camera.h"



=======
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
class MasterRenderer
{
public:
	MasterRenderer();
	~MasterRenderer();
private:
	void render();
	void initInstance();
	void setupDebugCallback();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createRenderPass();
	void createImageViews();
	void createFramebuffers();
	void createSemaphores();
	void createCommandPools();
<<<<<<< HEAD
	void createDepthResources();
	void createCommandBuffer(VkFramebuffer& framebuffer);
	void recreateSwapChain();
	static void windowResized(GLFWwindow* window, int width, int height);
	static void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mousePressed(GLFWwindow* window, int button, int action, int mods);
	static void mouseMove(GLFWwindow* window, double xPos, double yPos);

=======
	void createCommandBuffer(VkFramebuffer& framebuffer);
	void recreateSwapChain();
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
	VulkanContext* context;
	VkCommandBuffer primaryCommandBuffer;//submitted for execution
	VkFence renderFence;
	//Holds all sub-renderers
	TileRenderer* tileRenderer;
<<<<<<< HEAD
	TerrainRenderer* terrainRenderer;

	float frameTimer;
	// Use to adjust mouse rotation speed
	float rotationSpeed = 1.0f;
	// Use to adjust mouse zoom speed
	float zoomSpeed = 1.0f;

	Camera* camera;

	float zoom = 0;
	glm::vec3 rotation = glm::vec3();
	glm::vec3 cameraPos = glm::vec3();
	glm::vec2 mousePos;

	static bool leftMouseDown;
	static bool rightMouseDown;
=======
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c

};