#pragma once

#include "AudioClip.h"
#include <glm/vec3.hpp>

namespace Zenith
{
	class AudioSource
	{
	public:
		AudioSource();
		~AudioSource();

		void Play(AudioClip* clip);

		float GetPitch() const noexcept;
		float GetGain() const noexcept;
		glm::vec3 GetPosition() const noexcept;
		glm::vec3 GetVelocity() const noexcept;
		bool GetLoop() const noexcept;

		void SetPitch(float pitch) noexcept;
		void SetGain(float gain) noexcept;
		void SetPosition(const glm::vec3& position) noexcept;
		void SetVelocity(const glm::vec3& velocity) noexcept;
		void SetLoop(bool loop) noexcept;

	private:
		unsigned int m_Source = 0;
		float m_Pitch = 1.0f;
		float m_Gain = 1.0f;
		glm::vec3 m_Position{ 0.0f };
		glm::vec3 m_Velocity{ 0.0f };
		bool m_Loop = false;
		unsigned int m_Buffer = 0;
	};
}
