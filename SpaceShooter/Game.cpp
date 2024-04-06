#include "Game.hpp"
#include <iostream>

sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : m_window(sf::VideoMode(640, 480), "SFML Space Shooter")
{
	m_window.setVerticalSyncEnabled(true);

	m_world = std::make_unique<World>(m_window);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;
	while (m_window.isOpen())
	{
		deltaTime = clock.restart();
		
		//std::cout << deltaTime.asMicroseconds() << std::endl;
		
		processEvents();
		//update();
		//m_world->update(deltaTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			m_window.close();
			break;
		}
	}
}

void Game::update()
{
}

void Game::render()
{
	m_world->draw();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		m_IsMovingUp == isPressed;
	if (key == sf::Keyboard::S)
		m_IsMovingDown == isPressed;
	if (key == sf::Keyboard::A)
		m_IsMovingLeft == isPressed;
	if (key == sf::Keyboard::D)
		m_IsMovingRight == isPressed;
}
