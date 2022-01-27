#include "Renderer/Shader.h"

#include "Renderer/Renderer.h"

#include <fstream>
#include <sstream>
#include <string>

Shader::Shader(const std::string& filepath, bool binary)
	: ShaderBase(), m_FilePath(filepath)
{
	if (binary)
	{
		Renderer::Submit([&]() {
			// Process for loading binary is very abstracted :)
			m_RendererID = glCreateProgram();

			ShaderBinary binaryData = ShaderBinary::LoadFile(m_FilePath);
			LoadBinary(binaryData);
			binaryData.Free();
		});
	}
	else
	{
		Renderer::Submit([&]() {
			ShaderProgramSource source = ParseShader(m_FilePath);
			m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
		});
	}
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

uint32_t Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader, m_FilePath + " (Vertex Shader)");
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader, m_FilePath + " (Fragment Shader)");

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}