#ifndef CCUBEMAP_HPP
#define CCUBEMAP_HPP

#include <vector>
#include <string>
#include <iostream>

#include <gl/glew.h>
#include <stb/stb_image.h>

class CCubeMap
{
public:
	CCubeMap(std::vector<std::string> faces);
	~CCubeMap();

	void Draw();

	unsigned int GetTexture();

private:
	unsigned int m_VAO;
	unsigned int m_VBO;

	unsigned int m_Id;
};

#endif // CCUBEMAP_HPP
