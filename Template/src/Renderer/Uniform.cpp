#include "Renderer/Uniform.h"

#include "Renderer.h"

// Standard Vector Types

//		Uniform1f

Uniform1f::Uniform1f(float value)
	: m_Value(value) {}

void Uniform1f::Set(int32_t location)
{
	glUniform1f(location, m_Value);
}

//		Uniform2f

Uniform2f::Uniform2f(glm::vec2 value)
	: m_Value(value) {}

void Uniform2f::Set(int32_t location)
{
	glUniform2f(location, m_Value.x, m_Value.y);
}

//		Uniform3f

Uniform3f::Uniform3f(glm::vec3 value)
	: m_Value(value) {}

void Uniform3f::Set(int32_t location)
{
	glUniform3f(location, m_Value.x, m_Value.y, m_Value.z);
}

//		Uniform4f

Uniform4f::Uniform4f(glm::vec4 value)
	: m_Value(value) {}

void Uniform4f::Set(int32_t location)
{
	glUniform4f(location, m_Value.x, m_Value.y, m_Value.z, m_Value.w);
}


//		Uniform1i

Uniform1i::Uniform1i(int32_t value)
	: m_Value(value) {}

void Uniform1i::Set(int32_t location)
{
	glUniform1i(location, m_Value);
}

//		Uniform2i

Uniform2i::Uniform2i(glm::ivec2 value)
	: m_Value(value) {}

void Uniform2i::Set(int32_t location)
{
	glUniform2i(location, m_Value.x, m_Value.y);
}

//		Uniform3i

Uniform3i::Uniform3i(glm::ivec3 value)
	: m_Value(value) {}

void Uniform3i::Set(int32_t location)
{
	glUniform3i(location, m_Value.x, m_Value.y, m_Value.z);
}

//		Uniform4i

Uniform4i::Uniform4i(glm::ivec4 value)
	: m_Value(value) {}

void Uniform4i::Set(int32_t location)
{
	glUniform4i(location, m_Value.x, m_Value.y, m_Value.z, m_Value.w);
}

//		Uniform1ui

Uniform1ui::Uniform1ui(uint32_t value)
	: m_Value(value) {}

void Uniform1ui::Set(int32_t location)
{
	glUniform1ui(location, m_Value);
}

//		Uniform2ui

Uniform2ui::Uniform2ui(glm::uvec2 value)
	: m_Value(value) {}

void Uniform2ui::Set(int32_t location)
{
	glUniform2ui(location, m_Value.x, m_Value.y);
}

//		Uniform3ui

Uniform3ui::Uniform3ui(glm::uvec3 value)
	: m_Value(value) {}

void Uniform3ui::Set(int32_t location)
{
	glUniform3ui(location, m_Value.x, m_Value.y, m_Value.z);
}

//		Uniform4ui

Uniform4ui::Uniform4ui(glm::uvec4 value)
	: m_Value(value) {}

void Uniform4ui::Set(int32_t location)
{
	glUniform4ui(location, m_Value.x, m_Value.y, m_Value.z, m_Value.w);
}


// Vector Array Types

//		Uniform1fv

Uniform1fv::Uniform1fv(const std::vector<float>& values)
	: m_Values(values) {}

void Uniform1fv::Set(int32_t location)
{
	glUniform1fv(location, static_cast<int32_t>(m_Values.size()), m_Values.data());
}

//		Uniform2fv

Uniform2fv::Uniform2fv(const std::vector<glm::vec2>& values)
	: m_Values(values) {}

void Uniform2fv::Set(int32_t location)
{
	glUniform2fv(location, static_cast<int32_t>(m_Values.size()), reinterpret_cast<float*>(m_Values.data()));
}

//		Uniform3fv

Uniform3fv::Uniform3fv(const std::vector<glm::vec3>& values)
	: m_Values(values) {}

void Uniform3fv::Set(int32_t location)
{
	glUniform3fv(location, static_cast<int32_t>(m_Values.size()), reinterpret_cast<float*>(m_Values.data()));
}

//		Uniform4fv

Uniform4fv::Uniform4fv(const std::vector<glm::vec4>& values)
	: m_Values(values) {}

void Uniform4fv::Set(int32_t location)
{
	glUniform4fv(location, static_cast<int32_t>(m_Values.size()), reinterpret_cast<float*>(m_Values.data()));
}

//		Uniform1iv

Uniform1iv::Uniform1iv(const std::vector<int32_t>& values)
	: m_Values(values) {}

void Uniform1iv::Set(int32_t location)
{
	glUniform1iv(location, static_cast<int32_t>(m_Values.size()), m_Values.data());
}

//		Uniform2iv

Uniform2iv::Uniform2iv(const std::vector<glm::ivec2>& values)
	: m_Values(values) {}

void Uniform2iv::Set(int32_t location)
{
	glUniform2iv(location, static_cast<int32_t>(m_Values.size()), reinterpret_cast<int32_t*>(m_Values.data()));
}

//		Uniform3iv

Uniform3iv::Uniform3iv(const std::vector<glm::ivec3>& values)
	: m_Values(values) {}

void Uniform3iv::Set(int32_t location)
{
	glUniform3iv(location, static_cast<int32_t>(m_Values.size()), reinterpret_cast<int32_t*>(m_Values.data()));
}

//		Uniform4iv

Uniform4iv::Uniform4iv(const std::vector<glm::ivec4>& values)
	: m_Values(values) {}

void Uniform4iv::Set(int32_t location)
{
	glUniform4iv(location, static_cast<int32_t>(m_Values.size()), reinterpret_cast<int32_t*>(m_Values.data()));
}

//		Uniform1uiv

Uniform1uiv::Uniform1uiv(const std::vector<uint32_t>& values)
	: m_Values(values) {}

void Uniform1uiv::Set(int32_t location)
{
	glUniform1uiv(location, static_cast<int32_t>(m_Values.size()), m_Values.data());
}

//		Uniform2uiv

Uniform2uiv::Uniform2uiv(const std::vector<glm::uvec2>& values)
	: m_Values(values) {}

void Uniform2uiv::Set(int32_t location)
{
	glUniform2uiv(location, static_cast<int32_t>(m_Values.size()), reinterpret_cast<uint32_t*>(m_Values.data()));
}

//		Uniform3uiv

Uniform3uiv::Uniform3uiv(const std::vector<glm::uvec3>& values)
	: m_Values(values) {}

void Uniform3uiv::Set(int32_t location)
{
	glUniform3uiv(location, static_cast<int32_t>(m_Values.size()), reinterpret_cast<uint32_t*>(m_Values.data()));
}

//		Uniform4fv

Uniform4uiv::Uniform4uiv(const std::vector<glm::uvec4>& values)
	: m_Values(values) {}

void Uniform4uiv::Set(int32_t location)
{
	glUniform4uiv(location, static_cast<int32_t>(m_Values.size()), reinterpret_cast<uint32_t*>(m_Values.data()));
}


// Matrix Types

//		UniformMatrix2fv

UniformMatrix2fv::UniformMatrix2fv(const std::vector<glm::mat2>& values)
	: m_Values(values) {}

void UniformMatrix2fv::Set(int32_t location)
{
	glUniformMatrix2fv(location, static_cast<int32_t>(m_Values.size()), GL_FALSE, reinterpret_cast<float*>(m_Values.data()));
}

//		UniformMatrix3fv

UniformMatrix3fv::UniformMatrix3fv(const std::vector<glm::mat3>& values)
	: m_Values(values) {}

void UniformMatrix3fv::Set(int32_t location)
{
	glUniformMatrix3fv(location, static_cast<int32_t>(m_Values.size()), GL_FALSE, reinterpret_cast<float*>(m_Values.data()));
}

//		UniformMatrix4fv

UniformMatrix4fv::UniformMatrix4fv(const std::vector<glm::mat4>& values)
	: m_Values(values) {}

void UniformMatrix4fv::Set(int32_t location)
{
	glUniformMatrix4fv(location, static_cast<int32_t>(m_Values.size()), GL_FALSE, reinterpret_cast<float*>(m_Values.data()));
}

//		UniformMatrix2x3fv

UniformMatrix2x3fv::UniformMatrix2x3fv(const std::vector<glm::mat2x3>& values)
	: m_Values(values) {}

void UniformMatrix2x3fv::Set(int32_t location)
{
	glUniformMatrix2x3fv(location, static_cast<int32_t>(m_Values.size()), GL_FALSE, reinterpret_cast<float*>(m_Values.data()));
}

//		UniformMatrix3x2fv

UniformMatrix3x2fv::UniformMatrix3x2fv(const std::vector<glm::mat3x2>& values)
	: m_Values(values) {}

void UniformMatrix3x2fv::Set(int32_t location)
{
	glUniformMatrix3x2fv(location, static_cast<int32_t>(m_Values.size()), GL_FALSE, reinterpret_cast<float*>(m_Values.data()));
}

//		UniformMatrix2x4fv

UniformMatrix2x4fv::UniformMatrix2x4fv(const std::vector<glm::mat2x4>& values)
	: m_Values(values) {}

void UniformMatrix2x4fv::Set(int32_t location)
{
	glUniformMatrix2x4fv(location, static_cast<int32_t>(m_Values.size()), GL_FALSE, reinterpret_cast<float*>(m_Values.data()));
}

//		UniformMatrix4x2fv

UniformMatrix4x2fv::UniformMatrix4x2fv(const std::vector<glm::mat4x2>& values)
	: m_Values(values) {}

void UniformMatrix4x2fv::Set(int32_t location)
{
	glUniformMatrix4x2fv(location, static_cast<int32_t>(m_Values.size()), GL_FALSE, reinterpret_cast<float*>(m_Values.data()));
}

//		UniformMatrix3x4fv

UniformMatrix3x4fv::UniformMatrix3x4fv(const std::vector<glm::mat3x4>& values)
	: m_Values(values) {}

void UniformMatrix3x4fv::Set(int32_t location)
{
	glUniformMatrix3x4fv(location, static_cast<int32_t>(m_Values.size()), GL_FALSE, reinterpret_cast<float*>(m_Values.data()));
}

//		UniformMatrix4x3fv

UniformMatrix4x3fv::UniformMatrix4x3fv(const std::vector<glm::mat4x3>& values)
	: m_Values(values) {}

void UniformMatrix4x3fv::Set(int32_t location)
{
	glUniformMatrix4x3fv(location, static_cast<int32_t>(m_Values.size()), GL_FALSE, reinterpret_cast<float*>(m_Values.data()));
}