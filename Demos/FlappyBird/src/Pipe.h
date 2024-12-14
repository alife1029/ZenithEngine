#pragma once

#include <ZenithEngine.h>
#include <functional>
#include "Bird.h"

class Pipe
{
public:
	Pipe(Zenith::Texture2D* texture, float positionX, const glm::vec3& velocity, Bird* bird);

	void Update(std::function<void(int)> onBetweenGaps);
	void Render(Zenith::BatchRenderer* renderer);

public:
	glm::vec3 Position;
	glm::vec3 Velocity;

private:
	Zenith::Texture2D* m_Texture;
	const float m_Gap = 1.15f;
	Bird* m_Bird;
};
