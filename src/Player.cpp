#include "Player.hpp"


Player::Player() :
_texture(TextureFactory::Create("circle", TextureMode::mipmap))
{}

Player::~Player()
{
}

void Player::Render(glm::vec2 v)
{
	std::vector<Rectangle> rects;
	rects.push_back(Rectangle{1.0, 1.0, v, _texture.ID()});
	Rectangle::Render(rects);
}
