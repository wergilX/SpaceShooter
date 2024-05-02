#include "Player.hpp"
#include "Aircraft.hpp"
#include "AircraftMover.hpp"
#include <iostream>

const int playerSpeed = 5;

Player::Player()
{
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mActionBinding[MoveLeft].action =
		[](SceneNode& node, sf::Time dt)
	{
		node.move(-playerSpeed * dt.asSeconds(), 0.f);
	};
	mActionBinding[MoveRight].action =
		[](SceneNode& node, sf::Time dt)
	{
		node.move(playerSpeed * dt.asSeconds(), 0.f);
	};
	for(auto & pair: mActionBinding)
		pair.second.category = Category::PlayerAircraft;
}

void Player::handleEvent(const sf::Event& event,
	CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed
		&& event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [](SceneNode& s, sf::Time)
		{
			std::cout << s.getPosition().x << ","
				<< s.getPosition().y << "\n";
		};
		commands.push(output);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	for(auto pair: mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first)
			&& isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	return sf::Keyboard::Key();
}

bool Player::isRealtimeAction(Action action)
{
	return false;
}
