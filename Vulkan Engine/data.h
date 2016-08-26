#pragma once
#include <map>
#include "renderable.h"
class Data
{
public:
	
private:
	std::vector<Renderable*> renderableTargets;
	std::vector<VkCommandBuffer> availableCommandBuffers;
	std::map<int, int> cmdBufferMapping;
	
};