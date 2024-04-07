#include "Stars.hpp"
#include<iostream>

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
}
