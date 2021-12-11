#pragma once

#include <string>
#include <map>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind();

	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	std::string m_FilePath;
	uint32_t m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	bool m_Bound = false;
	bool m_CachedUniforms = false;

	static uint32_t m_BoundRendererID;

	// Uniform Caches
	std::map<std::string, int> m_Uniform1iCache;
	std::map<std::string, float> m_Uniform1fCache;
	std::map<std::string, glm::vec4> m_Uniform4fCache;
	std::map<std::string, glm::mat4> m_UniformMat4Cache;

private:
	ShaderProgramSource ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
	void SetUniforms();
};