#pragma once

#include <string>
#include <cstdint>
#include "ZenithException.h"

namespace Zenith
{
	class File
	{
	public:
		class CannotOpenFileException : public ZenithException
		{
		public:
			CannotOpenFileException(int line, const char* file, const std::string& path);
			const char* what() const noexcept override;
			virtual const char* GetType() const noexcept;

			std::string GetFilePath() const noexcept;

		private:
			std::string m_FilePath;
		};

		class CannotWriteFileException : public ZenithException
		{
		public:
			CannotWriteFileException(int line, const char* file, const std::string& path);
			const char* what() const noexcept override;
			virtual const char* GetType() const noexcept;

			std::string GetFilePath() const noexcept;

		private:
			std::string m_FilePath;
		};

	public:
		static std::string Read(const std::string& path);
		static uint8_t* ReadBinaryFile(const std::string & file);
		static void WriteBinaryFile(const std::string& path, const void* data, size_t dataLength);
	};
}
