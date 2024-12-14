#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Zenith
{
	struct Vertex
	{
		glm::vec3	Position;
		glm::vec4	Color;
		glm::vec2	TextureCoords;
		float		TextureIndex;
	};
}
