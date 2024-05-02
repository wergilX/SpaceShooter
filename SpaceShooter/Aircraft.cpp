#include "Aircraft.hpp"

Textures::ID toTextureID(Aircraft::Type type)
{
	switch (type)
	{
	case Aircraft::Type::SpaceShip:
		return Textures::ID::SpaceShip;
	case Aircraft::Type::Support:
		return Textures::ID::Support;
	case Aircraft::Type::Insect:
		return Textures::ID::Insect;
	}
}


Aircraft::Aircraft(Type type, TextureHolder& textureHolder) :
	m_type(type), m_sprite(textureHolder.get(toTextureID(type)))
{
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

unsigned int Aircraft::getCategory() const
{
	switch (m_type)
	{
	case SpaceShip:
		return Category::PlayerAircraft;
	default:
		return Category::EnemyAircraft;
	}
}
