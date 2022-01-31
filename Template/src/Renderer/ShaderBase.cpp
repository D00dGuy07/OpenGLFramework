#include "Renderer/ShaderBase.h"

#include "glad/glad.h"

#include <iostream>
#include <fstream>

uint32_t ShaderBase::m_BoundRendererID = 0xFFFFFFFF;

ShaderBase::ShaderBase()
	: m_UniformLocationCache() {}

ShaderBase::~ShaderBase()
{
	uint32_t id = m_RendererID;
	Renderer::Submit([=]() {
		if (m_BoundRendererID == id)
			m_BoundRendererID = 0xFFFFFFFF;
		glDeleteProgram(id);
	});
}

// Shader Binary

void ShaderBinary::Free()
{
	free(Data);
	Data = NULL;
}

void ShaderBinary::WriteFile(const std::string& filePath)
{
	if (!Data)
		return;

	std::ofstream file(filePath, std::ios::trunc | std::ios::binary);

	// Minimal error checking
	if (!file.good())
		return;

	// I'm not sure if reordering for little/big endian is important here
	file.write(reinterpret_cast<char*>(&Length), sizeof(int32_t));
	file.write(reinterpret_cast<char*>(&Format), sizeof(uint32_t));
	file.write(reinterpret_cast<char*>(Data), Length);
	file.close();
}

ShaderBinary ShaderBinary::LoadFile(const std::string& filePath)
{
	std::ifstream file(filePath, std::ios::binary);

	// Will return NULL data if it can't open the file
	if (!file.good())
		return { 0, 0, NULL };

	ShaderBinary binary = { 0, 0, NULL };
	file.read(reinterpret_cast<char*>(&binary.Length), sizeof(int32_t));
	file.read(reinterpret_cast<char*>(&binary.Format), sizeof(uint32_t));

	binary.Data = static_cast<uint8_t*>(malloc(static_cast<size_t>(binary.Length)));
	file.read(reinterpret_cast<char*>(binary.Data), binary.Length);

	file.close();
	return binary;
}

ShaderBinary ShaderBase::GetBinary()
{
	int32_t binaryLength = 0;
	glGetProgramiv(m_RendererID, GL_PROGRAM_BINARY_LENGTH, &binaryLength);

	// Could probably put binaryLength in here but im filling it with glGetProgramBinary anyway
	ShaderBinary binaryStruct = { 0, 0, static_cast<uint8_t*>(malloc(binaryLength)) };
	glGetProgramBinary(m_RendererID, binaryLength, &binaryStruct.Length, &binaryStruct.Format, binaryStruct.Data);

	return binaryStruct;
}

void ShaderBase::LoadBinary(ShaderBinary binary)
{
	glProgramBinary(m_RendererID, binary.Format, binary.Data, binary.Length);
	glValidateProgram(m_RendererID);
}

// Shader compilations

uint32_t ShaderBase::CompileShader(uint32_t type, const std::string& source, const std::string& identifier)
{
	uint32_t shader = glCreateShader(type);
	const char* src = source.c_str(); // glShaderSource takes a pointer to a pointer
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	return CheckErrors(shader, identifier);
}

uint32_t ShaderBase::CheckErrors(uint32_t shaderHandle, const std::string& identifier)
{
	int32_t result = 0;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int32_t length = 0;
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &length);
		char* message = static_cast<char*>(_malloca(length));
		glGetShaderInfoLog(shaderHandle, length, &length, message);

		// Could query GL_SHADER_TYPE for more error info
		std::cout << "[Shader Compilation] Compilation of " << identifier << " failed: \n\t" << message << '\n';
		_freea(message);

		glDeleteShader(shaderHandle);
		return 0;
	}

	return shaderHandle;
}

// Misc

void ShaderBase::Bind()
{
	Renderer::Submit([=]() {
		if (m_BoundRendererID == m_RendererID)
			return;
		m_BoundRendererID = m_RendererID;
		glUseProgram(m_RendererID);
	});

	if (m_CachedUniforms)
		SetUniforms();
}

// Uniform Setting

int ShaderBase::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}

void ShaderBase::SetUniforms()
{
	// Submits a render function that will set any uniforms that are cached at the
	// time of this render function being called in the render queue, not the uniforms
	// cached when SetUniforms is called
	Renderer::Submit([=]() {
		if (!m_CachedUniforms)
			return;

		for (auto& uPair : m_UniformCache)
		{
			uPair.second->Set(GetUniformLocation(uPair.first));
			delete uPair.second;
		}
		m_UniformCache.clear();

		m_CachedUniforms = false;
	});
}