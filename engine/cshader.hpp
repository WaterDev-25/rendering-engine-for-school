#ifndef CSHADER_HPP
#define CSHADER_HPP

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>

class CShader
{
public:
	CShader(std::string vPath, std::string fPath);
	~CShader();

	void Use();

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetVec2(const std::string& name, const glm::vec2& value) const;
	void SetVec2(const std::string& name, float x, float y) const;
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;
	void SetVec4(const std::string& name, const glm::vec4& value) const;
	void SetVec4(const std::string& name, float x, float y, float z, float w) const;
	void SetMat2(const std::string& name, const glm::mat2& value) const;
	void SetMat3(const std::string& name, const glm::mat3& value) const;
	void SetMat4(const std::string& name, const glm::mat4& value) const;

private:
	unsigned int m_Id;
};

#endif // CSHADER_HPP
