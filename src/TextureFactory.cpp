#include "TextureFactory.hpp"

#include <iostream>

std::unordered_map<std::string, GLuint> TextureFactory::_cache;

GLuint TextureFactory::Create(const std::string& identifier, TextureMode mode)
{
	if (_cache.count(identifier) == 0)
	{
		std::cout << "something" << std::endl;
		uint32_t id;
		__generate_texture(identifier.data(),
			identifier.length(),
			static_cast<uint8_t>(mode),
			&id);
		_cache[identifier] = id;
	}
	return _cache[identifier];
}
