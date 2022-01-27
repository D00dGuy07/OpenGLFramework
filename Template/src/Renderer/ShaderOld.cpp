#include "Renderer/Renderer.h"
#include "Renderer/ShaderOld.h"


#include "glad/glad.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>

uint32_t Shader::m_BoundRendererID = 0xFFFFFFFF;

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
	Renderer::Submit([&, filepath]() {
		ShaderProgramSource source = ParseShader(filepath);
		m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
	});
}

Shader::~Shader()
{
	uint32_t id = m_RendererID;
	Renderer::Submit([=]() {
		if (m_BoundRendererID == id)
			m_BoundRendererID = 0xFFFFFFFF;
		glDeleteProgram(id);
	});
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::Bind()
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

void Shader::SetUniform1i(const std::string& name, int value)
{
	m_Uniform1iCache[name] = value;
	m_CachedUniforms = true;
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	m_Uniform1fCache[name] = value;
	m_CachedUniforms = true;
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	m_Uniform4fCache[name] = glm::vec4(v0, v1, v2, v3);
	m_CachedUniforms = true;
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	m_UniformMat4Cache[name] = matrix;
	m_CachedUniforms = true;
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}

void Shader::SetUniforms()
{
	if (!m_CachedUniforms)
		return;

	// int
	for (auto& i : m_Uniform1iCache)
	{
		Renderer::Submit([=]() {
			glUniform1i(GetUniformLocation(i.first), i.second);
		});
	}
	m_Uniform1iCache.clear();

	// float
	for (auto& i : m_Uniform1fCache)
	{
		Renderer::Submit([=]() {
			glUniform1f(GetUniformLocation(i.first), i.second);
		});
	}
	m_Uniform1fCache.clear();

	// vec4
	for (auto& i : m_Uniform4fCache)
	{
		Renderer::Submit([=]() {
			glUniform4f(GetUniformLocation(i.first), i.second.x, i.second.y, i.second.z, i.second.w);
		});
	}
	m_Uniform4fCache.clear();

	// mat4
	for (auto& i : m_UniformMat4Cache)
	{
		Renderer::Submit([=]() {
			glUniformMatrix4fv(GetUniformLocation(i.first), 1, GL_FALSE, &i.second[0][0]);
		});
	}
	m_UniformMat4Cache.clear();

	m_CachedUniforms = false;
}
