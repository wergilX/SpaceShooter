#pragma once
#include<SFML/Graphics.hpp>

#include"World.hpp"

class Game
{
public:
	Game();
	void run();
private:
	void processEvents();
	void update();
	void render();

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
	sf::RenderWindow m_window;
	std::unique_ptr<World> m_world;

	bool m_IsMovingUp = false;
	bool m_IsMovingDown = false;
	bool m_IsMovingLeft = false;
	bool m_IsMovingRight = false;
};

