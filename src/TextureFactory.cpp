#include "TextureFactory.hpp"

std::unordered_map<std::string, GLuint> TextureFactory::_cache;

GLuint TextureFactory::Create(const std::string& identifier, TextureMode mode)
{
	if (_cache.count(identifier) == 0)
	{
		uint32_t id;
		__generate_texture(identifier.data(),
			identifier.length(),
			static_cast<uint8_t>(mode),
			&id);
		_cache[identifier] = id;
	}
	return _cache[identifier];
}
