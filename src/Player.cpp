#include "Player.hpp"


Player::Player() :
_texture(TextureFactory::Create("circle", TextureMode::mipmap))
{}

Player::~Player()
{
}

void Player::Render()
{
	std::vector<Rectangle> rects;
	rects.push_back(Rectangle{1.0, 1.0, glm::vec2(0.0), _texture.ID()});
	Rectangle::Render(rects);
}
