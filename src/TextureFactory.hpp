#pragma once

#include <stdint.h>
#include "graphic_core.hpp"
#include "Texture.hpp"

extern "C" {
	void __generate_texture(
		const char* identifier,
		size_t len,
		uint8_t mode,
		uint32_t* id);
}

enum class TextureMode : uint8_t
{
	nearest = 0,
	mipmap = 1
};

class TextureFactory
{
public:
	static GLuint Create(const std::string& identifier, TextureMode);
};
