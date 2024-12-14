#include "zenithpch.h"
#include "AudioClip.h"

#include <sndfile.h>
#include <cinttypes>
#include <AL/alext.h>

namespace Zenith
{
	AudioClip::AudioClip(const std::string& audioFile)
	{
		ALenum err;
		SNDFILE* sndFile;
		SF_INFO sfInfo;
		short* memBuf;
		sf_count_t numFrames;
		ALsizei numBytes;

		// Open the audio file and check that it is usable
		sndFile = sf_open(audioFile.c_str(), SFM_READ, &sfInfo);
		if (!sndFile)
		{
			throw ResourceNotFoundException(__LINE__, __FILE__, audioFile.c_str());
		}

		if (sfInfo.frames < 1 || sfInfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfInfo.channels)
		{
			sf_close(sndFile);
			throw BadSampleCountException(__LINE__, __FILE__, audioFile, sfInfo.frames);
		}

		// Get the sound format
		m_Format = AL_NONE;
		if (sfInfo.channels == 1) m_Format = AL_FORMAT_MONO16;
		else if (sfInfo.channels == 2) m_Format = AL_FORMAT_STEREO16;
		else if (sfInfo.channels == 3)
		{
			if (sf_command(sndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				m_Format = AL_FORMAT_BFORMAT2D_16;
		}
		else if (sfInfo.channels == 4)
		{
			if (sf_command(sndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				m_Format = AL_FORMAT_BFORMAT3D_16;
		}

		if (!m_Format)
		{
			sf_close(sndFile);
			throw UnsupportedChannelCountException(__LINE__, __FILE__, audioFile, sfInfo.channels);
		}

		// Decode the whole audio file to the buffer
		memBuf = (short*)(malloc((size_t)(sfInfo.frames * sfInfo.channels) * sizeof(short)));

		numFrames = sf_readf_short(sndFile, memBuf, sfInfo.frames);
		if (numFrames < 1)
		{
			free(memBuf);
			sf_close(sndFile);
			throw BadSampleCountException(__LINE__, __FILE__, audioFile, sfInfo.frames);
		}

		numBytes = (ALsizei)(numFrames * sfInfo.channels) * (ALsizei)sizeof(short);

		// Create OpenAL buffer
		alGenBuffers(1, &m_Buffer);
		alBufferData(m_Buffer, m_Format, memBuf, numBytes, sfInfo.samplerate);

		m_SampleRate = sfInfo.samplerate;

		free(memBuf);
		sf_close(sndFile);

		// Check if an error occured
		err = alGetError();
		if (err != AL_NO_ERROR)
		{
			if (m_Buffer && alIsBuffer(m_Buffer))
				alDeleteBuffers(1, &m_Buffer);

			throw OpenALException(__LINE__, __FILE__, alGetString(err));
		}
	}

	AudioClip::~AudioClip()
	{
		alDeleteBuffers(1, &m_Buffer);
	}
	
	unsigned int AudioClip::GetBuffer() const noexcept
	{
		return m_Buffer;
	}

#pragma region Exceptions

	AudioClip::BadSampleCountException::BadSampleCountException(int line, const char* file, const std::string& audioFile, int64_t sampleCount)
		:
		ZenithException(line, file), m_AudioFile(audioFile), m_SampleCount(sampleCount)
	{
	}
	const char* AudioClip::BadSampleCountException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Audio File] " << GetAudioFile() << std::endl
			<< "[Sample Count] " << GetSampleCount() << std::endl
			<< GetOriginString();
		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
	const char* AudioClip::BadSampleCountException::GetType() const noexcept
	{
		return "Bad Sample Count";
	}
	std::string AudioClip::BadSampleCountException::GetAudioFile() const noexcept
	{
		return m_AudioFile;
	}
	int64_t AudioClip::BadSampleCountException::GetSampleCount() const noexcept
	{
		return m_SampleCount;
	}

	AudioClip::UnsupportedChannelCountException::UnsupportedChannelCountException(int line, const char* file, const std::string& audioFile, int64_t channelCount)
		:
		ZenithException(line, file), m_AudioFile(audioFile), m_ChannelCount(channelCount)
	{
	}
	const char* AudioClip::UnsupportedChannelCountException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Audio File] " << GetAudioFile() << std::endl
			<< "[Channel Count] " << GetChannelCount() << std::endl
			<< GetOriginString();
		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
	const char* AudioClip::UnsupportedChannelCountException::GetType() const noexcept
	{
		return "Unsupported Audio Channel";
	}
	std::string AudioClip::UnsupportedChannelCountException::GetAudioFile() const noexcept
	{
		return m_AudioFile;
	}
	int64_t AudioClip::UnsupportedChannelCountException::GetChannelCount() const noexcept
	{
		return m_ChannelCount;
	}

	AudioClip::OpenALException::OpenALException(int line, const char* file, const std::string& errorMessage)
		:
		ZenithException(line, file), m_ErrorMessage(errorMessage)
	{
	}
	const char* AudioClip::OpenALException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Error Message] " << GetErrorMessage() << std::endl
			<< GetOriginString();
		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
	const char* AudioClip::OpenALException::GetType() const noexcept
	{
		return "OpenAL Exception";
	}
	std::string AudioClip::OpenALException::GetErrorMessage() const noexcept
	{
		return m_ErrorMessage;
	}

#pragma endregion
}
