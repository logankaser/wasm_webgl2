#pragma once

#include <string>
#include "graphic_core.hpp"

class Texture
{
	GLuint _ID;
public:
	Texture(unsigned width, unsigned height, unsigned char* data);
	~Texture();

	static Texture	GenerateFromSVG(const std::string& filepath);
	
	GLuint ID();
};
