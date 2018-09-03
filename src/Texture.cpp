#include "Texture.hpp"

#include <iostream>

#define NANOSVG_IMPLEMENTATION
#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvg.h"
#include "nanosvgrast.h"

Texture*	Texture::GenerateFromSVG(const std::string& filepath)
{
	NSVGimage *image = NULL;
	NSVGrasterizer *rast = NULL;
	unsigned char* img = NULL;
	int w, h;
	const char* filename = filepath.c_str();

	image = nsvgParseFromFile(filename, "px", 96.0f);
	if (image == NULL)
		std::cerr << filepath << " was invalid" << std::endl;
	w = (int)image->width;
	h = (int)image->height;

	rast = nsvgCreateRasterizer();
	if (rast == NULL)
		std::cerr << "nsvg raster failed to init" << std::endl;

	img = new unsigned char[w * h * sizeof(int)];

	nsvgRasterize(rast, image, 0, 0, 1, img, w, h, w * 4);

	Texture* out = new Texture(w, h, img);
	
	delete img;
	nsvgDeleteRasterizer(rast);
	nsvgDelete(image);

	return out;
}

Texture::Texture(unsigned width, unsigned height, unsigned char* data)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D,
		     0,
		     GL_RGBA,
		     width,
		     height,
		     0,
		     GL_RGBA,
		     GL_UNSIGNED_BYTE,
		     data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_ID);
}

GLuint	Texture::ID()
{
	return _ID;
}
