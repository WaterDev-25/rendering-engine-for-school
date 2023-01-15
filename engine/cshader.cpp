#include "cshader.hpp"

CShader::CShader(std::string vPath, std::string fPath)
{
	std::string vCode;
	std::string fCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vPath);
		fShaderFile.open(fPath);
		
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vCode = vShaderStream.str();
		fCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "WARNING --- Shader not successfully read ---" << std::endl;
	}

	const char* vShaderCode = vCode.c_str();
	const char* fShaderCode = fCode.c_str();

	int success;
	char infoLog[512];

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "WARNING --- Shader compilation failed ---" << std::endl << infoLog << std::endl;
	}

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "WARNING --- Shader compilation failed ---" << std::endl << infoLog << std::endl;
	}

	this->m_Id = glCreateProgram();

	glAttachShader(this->m_Id, vertex);
	glAttachShader(this->m_Id, fragment);
	glLinkProgram(this->m_Id);

	glGetProgramiv(this->m_Id, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(this->m_Id, 512, NULL, infoLog);
		std::cout << "WARNING --- Program linking failed ---" << std::endl << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

CShader::~CShader()
{
	// --
}

void CShader::Use()
{
	glUseProgram(this->m_Id);
}

void CShader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->m_Id, name.c_str()), (int)value);
}

void CShader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(this->m_Id, name.c_str()), value);
}

void CShader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(this->m_Id, name.c_str()), value);
}

void CShader::SetVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(this->m_Id, name.c_str()), 1, &value[0]);
}

void CShader::SetVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(this->m_Id, name.c_str()), x, y);
}

void CShader::SetVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(this->m_Id, name.c_str()), 1, &value[0]);
}

void CShader::SetVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(this->m_Id, name.c_str()), x, y, z);
}

void CShader::SetVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(this->m_Id, name.c_str()), 1, &value[0]);
}

void CShader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(this->m_Id, name.c_str()), x, y, z, w);
}

void CShader::SetMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(this->m_Id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void CShader::SetMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(this->m_Id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void CShader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->m_Id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
