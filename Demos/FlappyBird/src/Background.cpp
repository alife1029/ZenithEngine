#include "Background.h"

using namespace Zenith;
using namespace glm;

Background::Background(Texture2D* tex, const vec3& vel)
	:
	m_Texture(tex), m_Pos({ 0.0f }), m_Velocity(vel)
{
}

void Background::Update()
{
	m_Pos += m_Velocity * Time::Delta();

	if (m_Pos.x <= -(float)m_Texture->GetWidth() / (2.0f * m_Texture->PixelPerUnit()))
	{
		m_Pos.x += (float)m_Texture->GetWidth() / m_Texture->PixelPerUnit();
	}
}

void Background::Render(BatchRenderer* renderer)
{
	for (float x = -5.0f * m_Texture->GetWidth() / m_Texture->PixelPerUnit(); x <= 5.0f * m_Texture->GetWidth() / m_Texture->PixelPerUnit(); x += (float)m_Texture->GetWidth() / m_Texture->PixelPerUnit())
	{
		renderer->DrawTexture(m_Texture, m_Pos + glm::vec3{ x, 0.0f, 0.0f });
	}
}
