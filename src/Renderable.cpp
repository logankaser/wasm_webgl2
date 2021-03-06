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

void Renderable::Render(glm::vec2 pos, glm::vec2 dir, float scale, float aspect)
{
	float angle = glm::acos(glm::dot(glm::normalize(dir), glm::vec2(0, 1)));
	std::vector<Rectangle> rects;
	rects.push_back(Rectangle{
		_size * scale,
		_size * scale,
		pos,
		_texture,
		angle,
		aspect});
	Rectangle::Render(rects);
}
