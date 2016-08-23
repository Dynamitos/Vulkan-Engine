#include "display.h"



Display::Display()
{
}

Display::~Display()
{
}

void Display::createDisplay()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window = glfwCreateWindow(600, 400, "Vulkan Test", nullptr, nullptr);

	lastFrameTime = glfwGetTime();
}


void Display::updateDisplay()
{
	glfwPollEvents();
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastFrameTime >= 1.0) { // If last prinf() was more than 1 sec ago
											  // printf and reset timer
		printf("%f ms/frame\n", 1000.0 / double(nbFrames));
		nbFrames = 0;
		lastFrameTime += 1.0;
	}
}
void Display::closeDisplay()
{
	glfwTerminate();
	//system("PAUSE");
}
bool Display::shouldClose()
{
	return glfwWindowShouldClose(window);
}

GLFWwindow * Display::getWindow()
{
	return window;
}

int Display::getWidth()
{
	return WIDTH;
}

int Display::getHeight()
{
	return HEIGHT;
}
