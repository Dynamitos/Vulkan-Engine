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
<<<<<<< HEAD
	void setResolution(int width, int height);
=======
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
	GLFWwindow* getWindow();
	bool shouldClose();
private:
	GLFWwindow* window;
<<<<<<< HEAD
	int WIDTH;
	int HEIGHT;
=======
	const int WIDTH = 800;
	const int HEIGHT = 600;
>>>>>>> 32fa936776b44eff7ac43e37a15c7dd9390fb28c
	float lastFrameTime;
	int nbFrames;
};

