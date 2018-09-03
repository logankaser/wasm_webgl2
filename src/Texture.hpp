#pragma once

#include <string>
#include "graphic_core.hpp"

class Texture
{
	std::shared_ptr<GLuint> _ID;
public:
	Texture(unsigned width, unsigned height, unsigned char* data);

	static Texture	GenerateFromSVG(const std::string& filepath);

	GLuint ID();
};
