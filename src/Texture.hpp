#pragma once

#include "graphic_core.hpp"

class Texture
{
	GLuint _ID;
public:
	Texture(unsigned width, unsigned height, unsigned char* data);
	~Texture();

	GLuint ID();
};
