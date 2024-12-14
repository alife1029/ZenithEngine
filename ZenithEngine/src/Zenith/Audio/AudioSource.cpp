#include "zenithpch.h"
#include "AudioSource.h"

#include <AL/al.h>

namespace Zenith
{
	AudioSource::AudioSource()
	{
		alGenSources(1, &m_Source);
		alSourcef(m_Source, AL_PITCH, m_Pitch);
		alSourcef(m_Source, AL_GAIN, m_Gain);
		alSource3f(m_Source, AL_POSITION, m_Position.x, m_Position.y, m_Position.z);
		alSource3f(m_Source, AL_VELOCITY, m_Velocity.x, m_Velocity.y, m_Velocity.z);
		alSourcei(m_Source, AL_LOOPING, m_Loop);
		alSourcei(m_Source, AL_BUFFER, m_Buffer);
	}

	AudioSource::~AudioSource()
	{
		alDeleteSources(1, &m_Source);
	}

	void AudioSource::Play(AudioClip* clip)
	{
		if (clip->GetBuffer() != m_Buffer)
		{
			m_Buffer = clip->GetBuffer();
			alSourcei(m_Source, AL_BUFFER, m_Buffer);
		}

		alSourcePlay(m_Source);
	}

	float AudioSource::GetPitch() const noexcept { return m_Pitch; }
	float AudioSource::GetGain() const noexcept { return m_Gain; }
	glm::vec3 AudioSource::GetPosition() const noexcept { return m_Position; }
	glm::vec3 AudioSource::GetVelocity() const noexcept { return m_Velocity; }
	bool AudioSource::GetLoop() const noexcept { return m_Loop; }
	
	void AudioSource::SetPitch(float pitch) noexcept 
	{ 
		m_Pitch = pitch;
		alSourcef(m_Source, AL_PITCH, pitch);
	}
	void AudioSource::SetGain(float gain) noexcept 
	{ 
		m_Gain = gain; 
		alSourcef(m_Source, AL_GAIN, gain);
	}
	void AudioSource::SetPosition(const glm::vec3& position) noexcept
	{
		m_Position = position;
		alSource3f(m_Source, AL_POSITION, position.x, position.y, position.z);
	}
	void AudioSource::SetVelocity(const glm::vec3& velocity) noexcept
	{
		m_Velocity = velocity;
		alSource3f(m_Source, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	}
	void AudioSource::SetLoop(bool loop) noexcept
	{
		m_Loop = loop;
		alSourcei(m_Source, AL_LOOPING, loop);
	}
}
