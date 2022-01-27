#pragma once

#include "glm/glm.hpp"

#include <stdint.h>
#include <vector>

// Uniform::Set function should not be called outside of a render submit, it has bare OpenGL calls!! 

// Base class of all uniform types
class Uniform
{
public:
	virtual ~Uniform() {}

	virtual void Set(int32_t location) = 0;
};


// Standard Vector Types


//		Float types

class Uniform1f : public Uniform
{
public:
	Uniform1f(float value);
	virtual ~Uniform1f() override {}

	virtual void Set(int32_t location) override;
private:
	float m_Value;
};

class Uniform2f : public Uniform
{
public:
	Uniform2f(glm::vec2 value);
	virtual ~Uniform2f() override {}

	virtual void Set(int32_t location) override;
private:
	glm::vec2 m_Value;
};

class Uniform3f : public Uniform
{
public:
	Uniform3f(glm::vec3 value);
	virtual ~Uniform3f() override {}

	virtual void Set(int32_t location) override;
private:
	glm::vec3 m_Value;
};

class Uniform4f : public Uniform
{
public:
	Uniform4f(glm::vec4 value);
	virtual ~Uniform4f() override {}

	virtual void Set(int32_t location) override;
private:
	glm::vec4 m_Value;
};

//		Integer types

class Uniform1i : public Uniform
{
public:
	Uniform1i(int32_t value);
	virtual ~Uniform1i() override {}

	virtual void Set(int32_t location) override;
private:
	int32_t m_Value;
};

class Uniform2i : public Uniform
{
public:
	Uniform2i(glm::ivec2 value);
	virtual ~Uniform2i() override {}

	virtual void Set(int32_t location) override;
private:
	glm::ivec2 m_Value;
};

class Uniform3i : public Uniform
{
public:
	Uniform3i(glm::ivec3 value);
	virtual ~Uniform3i() override {}

	virtual void Set(int32_t location) override;
private:
	glm::ivec3 m_Value;
};

class Uniform4i : public Uniform
{
public:
	Uniform4i(glm::ivec4 value);
	virtual ~Uniform4i() override {}

	virtual void Set(int32_t location) override;
private:
	glm::ivec4 m_Value;
};

//		Unsigned integer types

class Uniform1ui : public Uniform
{
public:
	Uniform1ui(uint32_t value);
	virtual ~Uniform1ui() override {}

	virtual void Set(int32_t location) override;
private:
	uint32_t m_Value;
};

class Uniform2ui : public Uniform
{
public:
	Uniform2ui(glm::uvec2 value);
	virtual ~Uniform2ui() override {}

	virtual void Set(int32_t location) override;
private:
	glm::uvec2 m_Value;
};

class Uniform3ui : public Uniform
{
public:
	Uniform3ui(glm::uvec3 value);
	virtual ~Uniform3ui() override {}

	virtual void Set(int32_t location) override;
private:
	glm::uvec3 m_Value;
};

class Uniform4ui : public Uniform
{
public:
	Uniform4ui(glm::uvec4 value);
	virtual ~Uniform4ui() override {}

	virtual void Set(int32_t location) override;
private:
	glm::uvec4 m_Value;
};


// Vector Array Types

//		Float Types

class Uniform1fv : public Uniform
{
public:
	Uniform1fv(const std::vector<float>& values);
	virtual ~Uniform1fv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<float> m_Values;
};

class Uniform2fv : public Uniform
{
public:
	Uniform2fv(const std::vector<glm::vec2>& values);
	virtual ~Uniform2fv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::vec2> m_Values;
};

class Uniform3fv : public Uniform
{
public:
	Uniform3fv(const std::vector<glm::vec3>& values);
	virtual ~Uniform3fv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::vec3> m_Values;
};

class Uniform4fv : public Uniform
{
public:
	Uniform4fv(const std::vector<glm::vec4>& values);
	virtual ~Uniform4fv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::vec4> m_Values;
};

//		Integer Types

class Uniform1iv : public Uniform
{
public:
	Uniform1iv(const std::vector<int32_t>& values);
	virtual ~Uniform1iv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<int32_t> m_Values;
};

class Uniform2iv : public Uniform
{
public:
	Uniform2iv(const std::vector<glm::ivec2>& values);
	virtual ~Uniform2iv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::ivec2> m_Values;
};

class Uniform3iv : public Uniform
{
public:
	Uniform3iv(const std::vector<glm::ivec3>& values);
	virtual ~Uniform3iv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::ivec3> m_Values;
};

class Uniform4iv : public Uniform
{
public:
	Uniform4iv(const std::vector<glm::ivec4>& values);
	virtual ~Uniform4iv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::ivec4> m_Values;
};

//		Unsigned Integer Types

class Uniform1uiv : public Uniform
{
public:
	Uniform1uiv(const std::vector<uint32_t>& values);
	virtual ~Uniform1uiv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<uint32_t> m_Values;
};

class Uniform2uiv : public Uniform
{
public:
	Uniform2uiv(const std::vector<glm::uvec2>& values);
	virtual ~Uniform2uiv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::uvec2> m_Values;
};

class Uniform3uiv : public Uniform
{
public:
	Uniform3uiv(const std::vector<glm::uvec3>& values);
	virtual ~Uniform3uiv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::uvec3> m_Values;
};

class Uniform4uiv : public Uniform
{
public:
	Uniform4uiv(const std::vector<glm::uvec4>& values);
	virtual ~Uniform4uiv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::uvec4> m_Values;
};

// Matrix Types

class UniformMatrix2fv : public Uniform
{
public:
	UniformMatrix2fv(const std::vector<glm::mat2>& values);
	virtual ~UniformMatrix2fv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::mat2> m_Values;
};

class UniformMatrix3fv : public Uniform
{
public:
	UniformMatrix3fv(const std::vector<glm::mat3>& values);
	virtual ~UniformMatrix3fv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::mat3> m_Values;
};

class UniformMatrix4fv : public Uniform
{
public:
	UniformMatrix4fv(const std::vector<glm::mat4>& values);
	virtual ~UniformMatrix4fv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::mat4> m_Values;
};

class UniformMatrix2x3fv : public Uniform
{
public:
	UniformMatrix2x3fv(const std::vector<glm::mat2x3>& values);
	virtual ~UniformMatrix2x3fv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::mat2x3> m_Values;
};

class UniformMatrix3x2fv : public Uniform
{
public:
	UniformMatrix3x2fv(const std::vector<glm::mat3x2>& values);
	virtual ~UniformMatrix3x2fv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::mat3x2> m_Values;
};

class UniformMatrix2x4fv : public Uniform
{
public:
	UniformMatrix2x4fv(const std::vector<glm::mat2x4>& values);
	virtual ~UniformMatrix2x4fv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::mat2x4> m_Values;
};

class UniformMatrix4x2fv : public Uniform
{
public:
	UniformMatrix4x2fv(const std::vector<glm::mat4x2>& values);
	virtual ~UniformMatrix4x2fv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::mat4x2> m_Values;
};

class UniformMatrix3x4fv : public Uniform
{
public:
	UniformMatrix3x4fv(const std::vector<glm::mat3x4>& values);
	virtual ~UniformMatrix3x4fv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::mat3x4> m_Values;
};

class UniformMatrix4x3fv : public Uniform
{
public:
	UniformMatrix4x3fv(const std::vector<glm::mat4x3>& values);
	virtual ~UniformMatrix4x3fv() override {}

	virtual void Set(int32_t location) override;
private:
	std::vector<glm::mat4x3> m_Values;
};