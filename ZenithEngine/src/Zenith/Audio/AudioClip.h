#pragma once

#include "Zenith/Utils/ZenithException.h"

#include <string>

namespace Zenith
{
	class AudioClip
	{
	public:
		class BadSampleCountException : public ZenithException
		{
		public:
			BadSampleCountException(int line, const char* file, const std::string& audioFile, int64_t sampleCount);
			const char* what() const noexcept override;
			const char* GetType() const noexcept;

			std::string GetAudioFile() const noexcept;
			int64_t GetSampleCount() const noexcept;

		private:
			std::string m_AudioFile;
			int64_t m_SampleCount;
		};

		class UnsupportedChannelCountException : public ZenithException
		{
		public:
			UnsupportedChannelCountException(int line, const char* file, const std::string& audioFile, int64_t channelCount);
			const char* what() const noexcept override;
			const char* GetType() const noexcept;

			std::string GetAudioFile() const noexcept;
			int64_t GetChannelCount() const noexcept;

		private:
			std::string m_AudioFile;
			int64_t m_ChannelCount;
		};

		class OpenALException : public ZenithException
		{
		public:
			OpenALException(int line, const char* file, const std::string& errorMessage);
			const char* what() const noexcept override;
			const char* GetType() const noexcept;

			std::string GetErrorMessage() const noexcept;
		
		private:
			std::string m_ErrorMessage;
		};

	public:
		AudioClip(const std::string& audioFile);
		~AudioClip();

		unsigned int GetBuffer() const noexcept;

	private:
		unsigned int m_Buffer;
		int m_SampleRate;
		int m_Format;
	};
}
