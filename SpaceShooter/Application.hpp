#pragma once
#include"StateStack.hpp"

class Application
{
public:

	void registerStates();
	void processInput();
	void update(sf::Time dt);
private:

	StateStack mStateStack;
	sf::RenderWindow mWindow;
};

