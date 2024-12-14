#pragma once

#include <ZenithEngine.h>

class Background
{
public:
	Background(Zenith::Texture2D* tex, const glm::vec3& vel);
	void Update();
	void Render(Zenith::BatchRenderer* renderer);

private:
	Zenith::Texture2D* m_Texture;
	glm::vec3 m_Pos;
	glm::vec3 m_Velocity;
};
