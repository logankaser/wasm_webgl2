#pragma once

#include <string>
#include "graphic_core.hpp"

class Texture
{
	std::shared_ptr<GLuint> _ID;
public:
	Texture(GLuint id);

	GLuint ID();
};
