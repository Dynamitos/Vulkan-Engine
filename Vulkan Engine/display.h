#pragma once

#include <vulkan\vulkan.h>
#include <GLFW\glfw3.h>
#include <stdio.h>

class Display
{
public:
	Display();
	~Display();
	void createDisplay();
	void updateDisplay();
	void closeDisplay();
	int getWidth();
	int getHeight();
	GLFWwindow* getWindow();
	bool shouldClose();
private:
	GLFWwindow* window;
	const int WIDTH = 800;
	const int HEIGHT = 600;
	float lastFrameTime;
	int nbFrames;
};

