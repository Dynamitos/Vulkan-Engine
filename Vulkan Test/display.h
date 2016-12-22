#ifndef DISPLAY_H
#define DISPLAY_H


#include <vulkan\vulkan.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <chrono>

class Display
{
public:
	void createDisplay();

	void updateDisplay();

	void closeDisplay();

	bool shouldClose();

	GLFWwindow* getWindow();

	int getWidth();
	int getHeight();
private:
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	GLFWwindow* window;
	int nbFrames;
	float lastFrameTime = 0;
};
#endif /* !DISPLAY_H */