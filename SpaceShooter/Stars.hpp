#pragma once
#include"Entity.hpp"
#include"ResourceHolder.hpp"

class Stars : public Entity
{
public:
	Stars(Textures::ID id, TextureHolder& textureHolder);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	virtual void updateCurrent(sf::Time dt);

private:
	sf::Sprite m_sprite;
};

