#pragma once
#include<SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable
{
public:
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;

private:
	virtual void update(sf::Time dt);

private:
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
};

