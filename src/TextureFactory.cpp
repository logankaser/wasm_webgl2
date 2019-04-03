#include "TextureFactory.hpp"


GLuint TextureFactory::Create(const std::string& identifier, TextureMode mode)
{
	uint32_t id;
	__generate_texture(identifier.data(),
		identifier.length(),
		static_cast<uint8_t>(mode),
		&id);
	return id;
}
