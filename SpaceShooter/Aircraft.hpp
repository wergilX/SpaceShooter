#pragma once
#include"Entity.hpp"

class Aircraft : public Entity
{
public:
	explicit Aircraft(Type type, TextureHolder& textureHolder);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type m_type;
	sf::Sprite m_sprite;
};

