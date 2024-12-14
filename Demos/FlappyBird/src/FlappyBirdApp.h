#pragma once

#include <ZenithEngine.h>

#include "Background.h"
#include "Bird.h"
#include "Pipe.h"

class FlappyBirdApp : public Zenith::ZenithApp
{
public:
	FlappyBirdApp();
	~FlappyBirdApp();
	virtual void Start();
	virtual void Update();

private:
	void StartGame();
	void ResetGame();

	void RenderObjects();
	void RenderUI();
	void RenderImGui();

private:
	void OnBirdBetweenPipes(bool isCollide);

private:
	Zenith::Shader			*m_Shader,
							*m_TextShader,
							*m_UiImageShader;
	Zenith::BatchRenderer*	m_Renderer;
	Zenith::Viewport*		m_Viewport;
	Zenith::Camera*			m_Camera;
	Zenith::Texture2D		*m_BackgroundTexture,
							*m_PipeTexture,
							*m_WhiteTexture;
	Zenith::Font			*m_PixelifySans,
							*m_Righteous;
	Zenith::UIRenderer*		m_UiRenderer;
	Zenith::AudioDevice*	m_AudioDevice = nullptr;
	Zenith::AudioSource		*m_UiAudioSource = nullptr,
							*m_DieAudioSource = nullptr,
							*m_ScoreAudioSource = nullptr,
							*m_ThemeAudioSource = nullptr;
	Zenith::AudioClip	*m_DieSfx = nullptr,
						*m_PointSfx = nullptr,
						*m_SwooshSfx = nullptr,
						*m_ThemeSong = nullptr;
	std::vector<Zenith::Texture2D*>	m_CharacterTextures;
	float m_ElapsedTime = 0.0f;

	unsigned int	m_Score = 0,
					m_HiScore = 0;

	bool m_BirdBetweenGaps = false;
	bool m_BirdNearPipes = false;

	bool m_GameRunning = false;
	bool m_FirstLaunched = true;

	Background* m_Bg;
	Bird* m_Bird;
	std::vector<Pipe*> m_Pipes;

	float m_FpsHistory[500]{ 0 };
};
