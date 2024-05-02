#include "SceneNode.hpp"
#include "Aircraft.hpp"

struct AircraftMover
{
	AircraftMover(float vx, float vy)
		: velocity(vx, vy)
	{
	}
	void operator() (SceneNode& node, sf::Time) const
	{
		Aircraft& aircraft = static_cast<Aircraft&>(node);
		aircraft.setVelocity(aircraft.getVelocity() + velocity);
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.setVelocity(aircraft.getVelocity() + velocity);
	}

	sf::Vector2f velocity;
};