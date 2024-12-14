#include "zenithpch.h"
#include "AudioDevice.h"

#include <AL/al.h>

namespace Zenith
{
	AudioDevice* AudioDevice::Get()
	{
		static AudioDevice* device = new AudioDevice();
		return device;
	}

	AudioDevice::AudioDevice()
	{
		m_ALCDevice = alcOpenDevice(nullptr);	// nullptr = Get default device
		if (!m_ALCDevice)
		{
			throw Exception(__LINE__, __FILE__, "Failed to get sound device");
		}

		m_ALCContext = alcCreateContext(m_ALCDevice, nullptr);
		if (!m_ALCContext)
		{
			throw Exception(__LINE__, __FILE__, "Failed to set sound context");
		}

		if (!alcMakeContextCurrent(m_ALCContext))
		{
			throw Exception(__LINE__, __FILE__, "Failed to make context current");
		}

		const ALCchar* name = nullptr;
		if (alcIsExtensionPresent(m_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
			name = alcGetString(m_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
		if (!name || alcGetError(m_ALCDevice) != AL_NO_ERROR)
			name = alcGetString(m_ALCDevice, ALC_DEVICE_SPECIFIER);
	}

	AudioDevice::~AudioDevice()
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(m_ALCContext);
		alcCloseDevice(m_ALCDevice);
	}

	AudioDevice::Exception::Exception(int line, const char* file, const std::string& errorMessage)
		:
		ZenithException(line, file), m_ErrorMessage(errorMessage)
	{
	}
	const char* AudioDevice::Exception::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Error Message] " << GetErrorMessage() << std::endl
			<< GetOriginString();
		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
	const char* AudioDevice::Exception::GetType() const noexcept
	{
		return "Audio Device Exception";
	}
	std::string AudioDevice::Exception::GetErrorMessage() const noexcept
	{
		return m_ErrorMessage;
	}
}
