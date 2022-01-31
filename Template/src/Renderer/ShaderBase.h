#pragma once

#include "Renderer/Uniform.h"

#include "glm/glm.hpp"

#include <unordered_map>
#include <vector>

struct ShaderBinary
{
	int32_t Length;
	uint32_t Format;
	uint8_t* Data;

	// Must be called to prevent memory leak any time a valid
	// data pointer is stored
	void Free();

	void WriteFile(const std::string& filePath);
	static ShaderBinary LoadFile(const std::string& filePath);
};

// ShaderBase class contains functions shared by compute
// and render shaders such as those necessary for uniform usage
class ShaderBase
{
public:

	ShaderBase();
	virtual ~ShaderBase(); // Deriving destructor is unessecary unless for functionality

	// Free must be called on the return value of this function
	ShaderBinary GetBinary();

	// Misc
	void Bind();

	// Uniform Functions
	inline void SetUniform1f(const std::string& name, const float& value, bool cache = true)
		{ SetUniform<float, Uniform1f>(name, value, cache); }
	inline void SetUniform2f(const std::string& name, const glm::vec2& value, bool cache = true)
		{ SetUniform<glm::vec2, Uniform2f>(name, value, cache); }
	inline void SetUniform3f(const std::string& name, const glm::vec3& value, bool cache = true)
		{ SetUniform<glm::vec3, Uniform3f>(name, value, cache); }
	inline void SetUniform4f(const std::string& name, const glm::vec4& value, bool cache = true)
		{ SetUniform<glm::vec4, Uniform4f>(name, value, cache); }

	inline void SetUniform1i(const std::string& name, const int32_t& value, bool cache = true)
		{ SetUniform<int32_t, Uniform1i>(name, value, cache); }
	inline void SetUniform2i(const std::string& name, const glm::ivec2& value, bool cache = true)
		{ SetUniform<glm::ivec2, Uniform2i>(name, value, cache); }
	inline void SetUniform3i(const std::string& name, const glm::ivec3& value, bool cache = true)
		{ SetUniform<glm::ivec3, Uniform3i>(name, value, cache); }
	inline void SetUniform4i(const std::string& name, const glm::ivec4& value, bool cache = true)
		{ SetUniform<glm::ivec4, Uniform4i>(name, value, cache); }

	inline void SetUniform1ui(const std::string& name, const uint32_t& value, bool cache = true)
		{ SetUniform<uint32_t, Uniform1ui>(name, value, cache); }
	inline void SetUniform2ui(const std::string& name, const glm::uvec2& value, bool cache = true)
		{ SetUniform<glm::uvec2, Uniform2ui>(name, value, cache); }
	inline void SetUniform3ui(const std::string& name, const glm::uvec3& value, bool cache = true)
		{ SetUniform<glm::uvec3, Uniform3ui>(name, value, cache); }
	inline void SetUniform4ui(const std::string& name, const glm::uvec4& value, bool cache = true)
		{ SetUniform<glm::uvec4, Uniform4ui>(name, value, cache); }

	inline void SetUniform1fv(const std::string& name, const std::vector<float>& values, bool cache = true)
		{ SetUniform<std::vector<float>, Uniform1fv>(name, values, cache); }
	inline void SetUniform2fv(const std::string& name, const std::vector<glm::vec2>& values, bool cache = true)
		{ SetUniform<std::vector<glm::vec2>, Uniform2fv>(name, values, cache); }
	inline void SetUniform3fv(const std::string& name, const std::vector<glm::vec3>& values, bool cache = true)
		{ SetUniform<std::vector<glm::vec3>, Uniform3fv>(name, values, cache); }
	inline void SetUniform4fv(const std::string& name, const std::vector<glm::vec4>& values, bool cache = true)
		{ SetUniform<std::vector<glm::vec4>, Uniform4fv>(name, values, cache); }

	inline void SetUniform1iv(const std::string& name, const std::vector<int32_t>& values, bool cache = true)
		{ SetUniform<std::vector<int32_t>, Uniform1iv>(name, values, cache); }
	inline void SetUniform2iv(const std::string& name, const std::vector<glm::ivec2>& values, bool cache = true)
		{ SetUniform<std::vector<glm::ivec2>, Uniform2iv>(name, values, cache); }
	inline void SetUniform3iv(const std::string& name, const std::vector<glm::ivec3>& values, bool cache = true)
		{ SetUniform<std::vector<glm::ivec3>, Uniform3iv>(name, values, cache); }
	inline void SetUniform4iv(const std::string& name, const std::vector<glm::ivec4>& values, bool cache = true)
		{ SetUniform<std::vector<glm::ivec4>, Uniform4iv>(name, values, cache); }

	inline void SetUniform1uiv(const std::string& name, const std::vector<uint32_t>& values, bool cache = true)
		{ SetUniform<std::vector<uint32_t>, Uniform1uiv>(name, values, cache); }
	inline void SetUniform2uiv(const std::string& name, const std::vector<glm::uvec2>& values, bool cache = true)
		{ SetUniform<std::vector<glm::uvec2>, Uniform2uiv>(name, values, cache); }
	inline void SetUniform3uiv(const std::string& name, const std::vector<glm::uvec3>& values, bool cache = true)
		{ SetUniform<std::vector<glm::uvec3>, Uniform3uiv>(name, values, cache); }
	inline void SetUniform4uiv(const std::string& name, const std::vector<glm::uvec4>& values, bool cache = true)
		{ SetUniform<std::vector<glm::uvec4>, Uniform4uiv>(name, values, cache); }

	// OpenGL only has uniform functions for arrays of matrices so I only made
	// matrix uniform classes for arrays. These inline functions convert a single
	// matrix into an array and call the relevant function for convenience
	inline void SetUniformMatrix2f(const std::string& name, const glm::mat2& value, bool cache = true)
		{ SetUniform<std::vector<glm::mat2>, UniformMatrix2fv>(name, std::vector<glm::mat2>{value}, cache); }
	inline void SetUniformMatrix3f(const std::string& name, const glm::mat3& value, bool cache = true)
		{ SetUniform<std::vector<glm::mat3>, UniformMatrix3fv>(name, std::vector<glm::mat3>{value}, cache); }
	inline void SetUniformMatrix4f(const std::string& name, const glm::mat4& value, bool cache = true)
		{ SetUniform<std::vector<glm::mat4>, UniformMatrix4fv>(name, std::vector<glm::mat4>{value}, cache); }

	inline void SetUniformMatrix2x3f(const std::string& name, const glm::mat2x3& value, bool cache = true)
		{ SetUniform<std::vector<glm::mat2x3>, UniformMatrix2x3fv>(name, std::vector<glm::mat2x3>{value}, cache); }
	inline void SetUniformMatrix3x2f(const std::string& name, const glm::mat3x2& value, bool cache = true)
		{ SetUniform<std::vector<glm::mat3x2>, UniformMatrix3x2fv>(name, std::vector<glm::mat3x2>{value}, cache); }
	inline void SetUniformMatrix2x4f(const std::string& name, const glm::mat2x4& value, bool cache = true)
		{ SetUniform<std::vector<glm::mat2x4>, UniformMatrix2x4fv>(name, std::vector<glm::mat2x4>{value}, cache); }
	inline void SetUniformMatrix4x2f(const std::string& name, const glm::mat4x2& value, bool cache = true)
		{ SetUniform<std::vector<glm::mat4x2>, UniformMatrix4x2fv>(name, std::vector<glm::mat4x2>{value}, cache); }
	inline void SetUniformMatrix3x4f(const std::string& name, const glm::mat3x4& value, bool cache = true)
		{ SetUniform<std::vector<glm::mat3x4>, UniformMatrix3x4fv>(name, std::vector<glm::mat3x4>{value}, cache); }
	inline void SetUniformMatrix4x3f(const std::string& name, const glm::mat4x3& value, bool cache = true)
		{ SetUniform<std::vector<glm::mat4x3>, UniformMatrix4x3fv>(name, std::vector<glm::mat4x3>{value}, cache); }

	inline void SetUniformMatrix2fv(const std::string& name, const std::vector<glm::mat2>& values, bool cache = true)
		{ SetUniform<std::vector<glm::mat2>, UniformMatrix2fv>(name, values, cache); }
	inline void SetUniformMatrix3fv(const std::string& name, const std::vector<glm::mat3>& values, bool cache = true)
		{ SetUniform<std::vector<glm::mat3>, UniformMatrix3fv>(name, values, cache); }
	inline void SetUniformMatrix4fv(const std::string& name, const std::vector<glm::mat4>& values, bool cache = true)
		{ SetUniform<std::vector<glm::mat4>, UniformMatrix4fv>(name, values, cache); }

	inline void SetUniformMatrix2x3fv(const std::string& name, const std::vector<glm::mat2x3>& values, bool cache = true)
		{ SetUniform<std::vector<glm::mat2x3>, UniformMatrix2x3fv>(name, values, cache); }
	inline void SetUniformMatrix3x2fv(const std::string& name, const std::vector<glm::mat3x2>& values, bool cache = true)
		{ SetUniform<std::vector<glm::mat3x2>, UniformMatrix3x2fv>(name, values, cache); }
	inline void SetUniformMatrix2x4fv(const std::string& name, const std::vector<glm::mat2x4>& values, bool cache = true)
		{ SetUniform<std::vector<glm::mat2x4>, UniformMatrix2x4fv>(name, values, cache); }
	inline void SetUniformMatrix4x2fv(const std::string& name, const std::vector<glm::mat4x2>& values, bool cache = true)
		{ SetUniform<std::vector<glm::mat4x2>, UniformMatrix4x2fv>(name, values, cache); }
	inline void SetUniformMatrix3x4fv(const std::string& name, const std::vector<glm::mat3x4>& values, bool cache = true)
		{ SetUniform<std::vector<glm::mat3x4>, UniformMatrix3x4fv>(name, values, cache); }
	inline void SetUniformMatrix4x3fv(const std::string& name, const std::vector<glm::mat4x3>& values, bool cache = true)
		{ SetUniform<std::vector<glm::mat4x3>, UniformMatrix4x3fv>(name, values, cache); }

protected:
	// A lot of the functions in here don't technically need to be protected and it might
	// the shader api more flexible if it isn't but for now it makes it a little cleaner

	uint32_t m_RendererID = 0;
	// Having BoundRendererID here assumes that all shaders use same binding points
	// and methods which is currently true for all shader types that I know of
	static uint32_t m_BoundRendererID;

	// Uniform caching
	std::unordered_map<std::string, int> m_UniformLocationCache;
	std::unordered_map<std::string, Uniform*> m_UniformCache;
	bool m_CachedUniforms = false;

	int GetUniformLocation(const std::string& name);
	void SetUniforms();

	// Shader compilation
	static uint32_t CompileShader(uint32_t type, const std::string& source, const std::string& identifier);
	static uint32_t CheckErrors(uint32_t shaderHandle, const std::string& identifier);

	// Misc
	void LoadBinary(ShaderBinary binary);

	// Uniform Templates

	template<typename argument, typename uniformType>
	void SetUniform(const std::string& name, const argument& value, bool cache)
	{
		if (!cache)
		{
			uniformType(value).Set(GetUniformLocation(name));
			return;
		}

		delete m_UniformCache[name];
		m_UniformCache[name] = new uniformType(value);
		m_CachedUniforms = true;
	}
};