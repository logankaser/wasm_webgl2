#include "Texture.hpp"

#include <iostream>
#include <stdint.h>

static void delete_texture(GLuint* id_ptr)
{
	glDeleteTextures(1, id_ptr);
	delete id_ptr;
}

Texture::Texture(GLuint id)
{
	_ID = std::shared_ptr<GLuint>(new GLuint(id), delete_texture);
}

GLuint	Texture::ID()
{
	return *_ID;
}
