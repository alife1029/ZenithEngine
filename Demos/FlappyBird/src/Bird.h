#pragma once

#include <ZenithEngine.h>

class Bird
{
public:
	Bird(Zenith::Texture2D** textures);
	~Bird();

	void Start();
	void Update(float timeElapsed);
	void Render(Zenith::BatchRenderer* renderer);
	
public:
	glm::vec3 Position;

private:
	Zenith::Texture2D** m_Textures;
	Zenith::Texture2D* m_CurrentTexture;
	glm::vec3 m_Velocity;
	float m_Rotation;

	Zenith::AudioSource* m_AudioSource;
	Zenith::AudioClip* m_WingSfx;
};
