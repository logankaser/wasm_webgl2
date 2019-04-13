#include "Renderable.hpp"

Renderable::Renderable(const game_protocol::Renderable& r)
{
	std::cout << "r made" << std::endl;
	_texture = TextureFactory::Create("circle", TextureMode::mipmap);
	_size = r.size();
	_color = r.color();
	std::cout << "hmm" << std::endl;
}

void Renderable::Update(const game_protocol::Renderable& r)
{
	_size = r.size();
	_color = r.color();
}

void Renderable::Render(glm::vec2 pos, glm::vec2 dir)
{
	(void)dir;
	std::vector<Rectangle> rects;
	rects.push_back(Rectangle{_size, _size, pos, _texture});
	Rectangle::Render(rects);
}
