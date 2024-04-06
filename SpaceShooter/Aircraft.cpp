#include "Aircraft.hpp"

Aircraft::Aircraft(Type type, TextureHolder& textureHolder) :
	m_type(type), m_sprite(textureHolder.get(toTextureID(type)))
{
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
