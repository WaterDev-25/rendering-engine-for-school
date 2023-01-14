#ifndef CSHADER_HPP
#define CSHADER_HPP

#include <string>

class CShader
{
public:
	CShader(std::string vPath, std::string fPath);
	~CShader();

	void Use();
};

#endif // CSHADER_HPP
