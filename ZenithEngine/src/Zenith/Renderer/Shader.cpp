#include "zenithpch.h"
#include "Shader.h"
#include "Zenith/Utils/File.h"

#define PARAMETER_UNIFORM_1N glGetUniformLocation(m_ProgramID, varName.c_str()), value
#define PARAMETER_UNIFORM_2N glGetUniformLocation(m_ProgramID, varName.c_str()), value.x, value.y
#define PARAMETER_UNIFORM_3N PARAMETER_UNIFORM_2N, value.z
#define PARAMETER_UNIFORM_4N PARAMETER_UNIFORM_3N, value.w
#define PARAMETER_UNIFORM_ARRAY glGetUniformLocation(m_ProgramID, varName.c_str()), arraySize, array
#define PARAMETER_UNIFORM_MATRIX glGetUniformLocation(m_ProgramID, varName.c_str()), 1, GL_FALSE, glm::value_ptr(value)

namespace Zenith
{
	static std::string PreprocessGLSL_Source(const std::string& src)
	{
		int maxTextures;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures);
		return std::regex_replace(src, std::regex("#define MAX_TEXTURES"), "#define MAX_TEXTURES " + std::to_string(maxTextures));
	}

	Shader::Shader(const std::string& vsFile, const std::string& fsFile)
	{
		m_ProgramID = glCreateProgram();
		AttachShader(vsFile, GL_VERTEX_SHADER);
		AttachShader(fsFile, GL_FRAGMENT_SHADER);
		LinkProgram();
	}
	Shader::~Shader()
	{
		glDeleteShader(m_ProgramID);
	}
	void Shader::Bind() const noexcept
	{
		glUseProgram(m_ProgramID);
	}
	uint32_t Shader::GetID() const noexcept
	{
		return m_ProgramID;
	}

	void Shader::AttachShader(const std::string& shaderFile, uint32_t type)
	{
		// Read shader source
		std::string _src = PreprocessGLSL_Source(File::Read(shaderFile));
		const char* src = _src.c_str();

		// Create & compile shader
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		// Compile errors
		int isCompiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (!isCompiled)
		{
			char log[1024];
			glGetShaderInfoLog(shader, 1024, nullptr, log);
			throw CompileError(__LINE__, __FILE__, shaderFile, log);
		}

		// Attach compiled shader
		glAttachShader(m_ProgramID, shader);

		// Cleanup
		glDeleteShader(shader);
	}

	void Shader::LinkProgram()
	{
		glLinkProgram(m_ProgramID);

		// Linkage errors
		int isLinked;
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &isLinked);
		if (!isLinked)
		{
			char log[1024];
			glGetProgramInfoLog(m_ProgramID, 1024, nullptr, log);
			throw LinkError(__LINE__, __FILE__, m_ProgramID, log);
		}
	}

#pragma region Uniform Setters

#pragma region Integer
	void Shader::SetUniformInt(const std::string& varName, int value) const noexcept
	{
		glUniform1i(PARAMETER_UNIFORM_1N);
	}
	void Shader::SetUniformIVec2(const std::string& varName, const glm::ivec2& value) const noexcept
	{
		glUniform2i(PARAMETER_UNIFORM_2N);
	}
	void Shader::SetUniformIVec3(const std::string& varName, const glm::ivec3& value) const noexcept
	{
		glUniform3i(PARAMETER_UNIFORM_3N);
	}
	void Shader::SetUniformIVec4(const std::string& varName, const glm::ivec4& value) const noexcept
	{
		glUniform4i(PARAMETER_UNIFORM_4N);
	}
	void Shader::SetUniformIntArray(const std::string& varName, int* array, int arraySize) const noexcept
	{
		glUniform1iv(PARAMETER_UNIFORM_ARRAY);
	}
#pragma endregion
#pragma region Unsigned Integer
	void Shader::SetUniformUInt(const std::string& varName, unsigned int value) const noexcept
	{
		glUniform1ui(PARAMETER_UNIFORM_1N);
	}
	void Shader::SetUniformUVec2(const std::string& varName, const glm::uvec2& value) const noexcept
	{
		glUniform2ui(PARAMETER_UNIFORM_2N);
	}
	void Shader::SetUniformUVec3(const std::string& varName, const glm::uvec3& value) const noexcept
	{
		glUniform3ui(PARAMETER_UNIFORM_3N);
	}
	void Shader::SetUniformUVec4(const std::string& varName, const glm::uvec4& value) const noexcept
	{
		glUniform4ui(PARAMETER_UNIFORM_4N);
	}
	void Shader::SetUniformUIntArray(const std::string& varName, unsigned int* array, int arraySize) const noexcept
	{
		glUniform1uiv(PARAMETER_UNIFORM_ARRAY);
	}
#pragma endregion
#pragma region Double
	void Shader::SetUniformDouble(const std::string& varName, double value) const noexcept
	{
		glUniform1d(PARAMETER_UNIFORM_1N);
	}
	void Shader::SetUniformDVec2(const std::string& varName, const glm::dvec2& value) const noexcept
	{
		glUniform2d(PARAMETER_UNIFORM_2N);
	}
	void Shader::SetUniformDVec3(const std::string& varName, const glm::dvec3& value) const noexcept
	{
		glUniform3d(PARAMETER_UNIFORM_3N);
	}
	void Shader::SetUniformDVec4(const std::string& varName, const glm::dvec4& value) const noexcept
	{
		glUniform4d(PARAMETER_UNIFORM_4N);
	}
	void Shader::SetUniformDoubleArray(const std::string& varName, double* array, int arraySize) const noexcept
	{
		glUniform1dv(PARAMETER_UNIFORM_ARRAY);
	}
	void Shader::SetUniformDMatrix2(const std::string& varName, const glm::dmat2& value) const noexcept
	{
		glUniformMatrix2dv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformDMatrix2x3(const std::string& varName, const glm::dmat2x3& value) const noexcept
	{
		glUniformMatrix2x3dv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformDMatrix2x4(const std::string& varName, const glm::dmat2x4& value) const noexcept
	{
		glUniformMatrix2x4dv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformDMatrix3x2(const std::string& varName, const glm::dmat3x2& value) const noexcept
	{
		glUniformMatrix3x2dv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformDMatrix3(const std::string& varName, const glm::dmat3& value) const noexcept
	{
		glUniformMatrix3dv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformDMatrix3x4(const std::string& varName, const glm::dmat3x4& value) const noexcept
	{
		glUniformMatrix3x4dv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformDMatrix4x2(const std::string& varName, const glm::dmat4x2& value) const noexcept
	{
		glUniformMatrix4x2dv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformDMatrix4x3(const std::string& varName, const glm::dmat4x3& value) const noexcept
	{
		glUniformMatrix4x3dv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformDMatrix4(const std::string& varName, const glm::dmat4& value) const noexcept
	{
		glUniformMatrix4dv(PARAMETER_UNIFORM_MATRIX);
	}
#pragma endregion
#pragma region Float
	void Shader::SetUniformFloat(const std::string& varName, float value) const noexcept
	{
		glUniform1f(PARAMETER_UNIFORM_1N);
	}
	void Shader::SetUniformVec2(const std::string& varName, const glm::vec2& value) const noexcept
	{
		glUniform2f(PARAMETER_UNIFORM_2N);
	}
	void Shader::SetUniformVec3(const std::string& varName, const glm::vec3& value) const noexcept
	{
		glUniform3f(PARAMETER_UNIFORM_3N);
	}
	void Shader::SetUniformVec4(const std::string& varName, const glm::vec4& value) const noexcept
	{
		glUniform4f(PARAMETER_UNIFORM_4N);
	}
	void Shader::SetUniformFloatArray(const std::string& varName, float* array, int arraySize) const noexcept
	{
		glUniform1fv(PARAMETER_UNIFORM_ARRAY);
	}
	void Shader::SetUniformMatrix2(const std::string& varName, const glm::mat2& value) const noexcept
	{
		glUniformMatrix2fv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformMatrix2x3(const std::string& varName, const glm::mat2x3& value) const noexcept
	{
		glUniformMatrix2x3fv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformMatrix2x4(const std::string& varName, const glm::mat2x4& value) const noexcept
	{
		glUniformMatrix2x4fv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformMatrix3x2(const std::string& varName, const glm::mat3x2& value) const noexcept
	{
		glUniformMatrix3x2fv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformMatrix3(const std::string& varName, const glm::mat3& value) const noexcept
	{
		glUniformMatrix3fv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformMatrix3x4(const std::string& varName, const glm::mat3x4& value) const noexcept
	{
		glUniformMatrix3x4fv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformMatrix4x2(const std::string& varName, const glm::mat4x2& value) const noexcept
	{
		glUniformMatrix4x2fv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformMatrix4x3(const std::string& varName, const glm::mat4x3& value) const noexcept
	{
		glUniformMatrix4x3fv(PARAMETER_UNIFORM_MATRIX);
	}
	void Shader::SetUniformMatrix4(const std::string& varName, const glm::mat4& value) const noexcept
	{
		glUniformMatrix4fv(PARAMETER_UNIFORM_MATRIX);
	}
#pragma endregion

#pragma endregion

#pragma region Exceptions
	Shader::CompileError::CompileError(int line, const char* file, const std::string& glslFile, const std::string& infoLog)
		:
		ZenithException(line, file), m_GlslFile(glslFile), m_InfoLog(infoLog)
	{
	}

	const char* Shader::CompileError::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[GLSL Source File] " << m_GlslFile << std::endl
			<< "\n[GPU Log] " << std::endl << m_InfoLog << std::endl
			<< "\n" << GetOriginString();
		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
	const char* Shader::CompileError::GetType() const noexcept
	{
		return "GLSL Shader Compilation Error";
	}
	std::string Shader::CompileError::GetGLSLSrcFile() const noexcept
	{
		return m_GlslFile;
	}
	std::string Shader::CompileError::GetGPULog() const noexcept
	{
		return m_InfoLog;
	}

	Shader::LinkError::LinkError(int line, const char* file, uint32_t shaderProgramID, const std::string& infoLog)
		:
		ZenithException(line, file), m_ProgramID(shaderProgramID), m_InfoLog(infoLog)
	{
	}
	const char* Shader::LinkError::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Program ID] 0x" << std::hex << std::uppercase << m_ProgramID << std::endl
			<< "\n[GPU Log]" << std::endl << m_InfoLog << std::endl
			<< "\n" << GetOriginString();
		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
	const char* Shader::LinkError::GetType() const noexcept
	{
		return "OpenGL Shader Pipeline Linkage Error";
	}
	uint32_t Shader::LinkError::GetProgramID() const noexcept
	{
		return m_ProgramID;
	}
	std::string Shader::LinkError::GetGPULog() const noexcept
	{
		return m_InfoLog;
	}
}
#pragma endregion
