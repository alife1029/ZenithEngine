#include "zenithpch.h"
#include "File.h"

namespace Zenith
{
#pragma region Exceptions
	File::CannotOpenFileException::CannotOpenFileException(int line, const char* file, const std::string& path)
		: 
		ZenithException(line, file), m_FilePath(path)
	{
	}
	const char* File::CannotOpenFileException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Problem File] " << GetFilePath() << std::endl
			<< GetOriginString();
		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
	const char* File::CannotOpenFileException::GetType() const noexcept
	{
		return "Cannot Open File";
	}
	std::string File::CannotOpenFileException::GetFilePath() const noexcept
	{
		return m_FilePath;
	}

	File::CannotWriteFileException::CannotWriteFileException(int line, const char* file, const std::string& path)
		:
		ZenithException(line, file), m_FilePath(path)
	{
	}
	const char* File::CannotWriteFileException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Problem File] " << GetFilePath() << std::endl
			<< GetOriginString();
		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
	const char* File::CannotWriteFileException::GetType() const noexcept
	{
		return "Cannot Write File";
	}
	std::string File::CannotWriteFileException::GetFilePath() const noexcept
	{
		return m_FilePath;
	}
#pragma endregion

	std::string File::Read(const std::string& path)
	{
		std::ifstream ifs(path);
		std::stringstream ret;

		if (ifs.is_open())
		{
			ret << ifs.rdbuf();
		}
		else
		{
			throw ResourceNotFoundException(__LINE__, __FILE__, path);
		}

		return ret.str();
	}

	uint8_t* File::ReadBinaryFile(const std::string& file)
	{
		std::ifstream ifs(file, std::ios::binary);
		if (!ifs)
		{
			throw ResourceNotFoundException(__LINE__, __FILE__, file);
		}
		
		ifs.seekg(0, ifs.end);
		const size_t fileSize = ifs.tellg();
		ifs.seekg(0, ifs.beg);

		uint8_t* data = (uint8_t*)malloc(fileSize);
		ifs.read((char*)data, fileSize);
		ifs.close();

		return data;
	}

	void File::WriteBinaryFile(const std::string& path, const void* data, size_t dataLength)
	{
		std::ofstream ofs(path, std::ios::binary);
		if (!ofs)
		{
			throw CannotOpenFileException(__LINE__, __FILE__, path);
		}

		int eof = 1;

		ofs.write((char*)data, dataLength);
		ofs.write((char*)&eof, sizeof(eof));
		ofs.close();

		if (!ofs.good())
		{
			throw CannotWriteFileException(__LINE__, __FILE__, path);
		}
	}
}
