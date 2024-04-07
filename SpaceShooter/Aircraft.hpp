#pragma once
#include"Entity.hpp"
#include"ResourceHolder.hpp"

class Aircraft : public Entity
{
public:
	enum Type
	{
		SpaceShip,
		Support,
		Insect,
	};
public:
	explicit Aircraft(Type type, TextureHolder& textureHolder);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type m_type;
	sf::Sprite m_sprite;
};

