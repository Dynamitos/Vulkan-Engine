#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "renderer.h"

int main()
{
	Renderer* renderer = new Renderer();
	renderer->startApp();
	return 0;
}