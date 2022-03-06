#pragma once
#include "glm/glm.hpp"


int StaticRectToStaticRect(glm::vec2 pos0, glm::vec2 scale0, glm::vec2 pos1, glm::vec2 scale1)
{
	if ((pos0.x - scale0.x) > (pos1.x + scale1.x)) {
		return 0;
	}

	if ((pos0.x + scale0.x) < (pos1.x - scale1.x)) {
		return 0;
	}

	if ((pos0.y + scale0.y) < (pos1.y - scale1.y)) {
		return 0;
	}

	if ((pos0.y - scale0.y) > (pos1.y + scale1.y)) {
		return 0;
	}

	return 1;

}