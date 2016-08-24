#pragma once
#include "utils.h"
class Renderable
{
	virtual VkCommandBuffer getCommandBuffer(VkCommandBufferInheritanceInfo inheritance) = 0;
};