#include "Stars.hpp"
#include<iostream>

constexpr float SCREEN_HEIGHT = 1000;

Stars::Stars(Textures::ID id, TextureHolder& textureHolder)
	:m_sprite(textureHolder.get(id))
{
}

void Stars::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

void Stars::updateCurrent(sf::Time dt)
{
	auto offset = (this->getVelocity().y * dt.asSeconds());
	this->move({0,offset});

	if (this->getPosition().y > SCREEN_HEIGHT)
	{
		this->setPosition(sf::Vector2f(0, -SCREEN_HEIGHT));
	}
}
