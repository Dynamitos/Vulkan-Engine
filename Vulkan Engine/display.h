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
	void setResolution(int width, int height);
	GLFWwindow* getWindow();
	bool shouldClose();
private:
	GLFWwindow* window;
	int WIDTH;
	int HEIGHT;
	float lastFrameTime;
	int nbFrames;
};

