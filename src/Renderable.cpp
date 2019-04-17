#include "Renderable.hpp"

Renderable::Renderable(const game_protocol::Renderable& r)
{
	_texture = TextureFactory::Create("circle", TextureMode::mipmap);
	_size = r.size();
	_color = r.color();
}

void Renderable::Update(const game_protocol::Renderable& r)
{
	_size = r.size();
	_color = r.color();
}

void Renderable::Render(glm::vec2 pos, glm::vec2 dir, glm::vec2 scale)
{
	(void)dir;
	std::vector<Rectangle> rects;
	rects.push_back(Rectangle{_size * scale.x, _size * scale.y, pos, _texture});
	Rectangle::Render(rects);
}
