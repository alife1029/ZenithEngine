#pragma once

#include "Zenith/Utils/ZenithException.h"

#include <AL/alc.h>

#include <string>

namespace Zenith
{
	class AudioDevice
	{
	public:
		class Exception : ZenithException
		{
		public:
			Exception(int line, const char* file, const std::string& errorMessage);
			const char* what() const noexcept override;
			const char* GetType() const noexcept;

			std::string GetErrorMessage() const noexcept;

		private:
			std::string m_ErrorMessage;
		};

	public:
		static AudioDevice* Get();

	private:
		AudioDevice();
		~AudioDevice();

		ALCdevice* m_ALCDevice;
		ALCcontext* m_ALCContext;
	};
}

