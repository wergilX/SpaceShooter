#include "Game.hpp"
#include <iostream>

sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : m_window(sf::VideoMode(1000, 1000), "SFML Space Shooter")
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
		if (!mIsPaused)
			update(deltaTime);

		deltaTime = clock.restart();
		render();
		processEvents();
	}
}

void Game::processEvents()
{
	CommandQueue& commands = m_world->getCommandQueue();
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		mPlayer.handleEvent(event, commands);
		if (event.type == sf::Event::Closed)
			m_window.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			commands.push(moveLeft);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			commands.push(moveRight);
	}
	mPlayer.handleRealtimeInput(commands);
}

void Game::update(sf::Time deltaTime)
{
	m_world->update(deltaTime);

	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		//movement.y -= PlayerSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		//movement.y += PlayerSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		//movement.x -= PlayerSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{ }
		//movement.x += PlayerSpeed;
	//m_player.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
	m_window.clear();
	m_world->draw();
	m_window.display();


	/*
	mWindow.clear();
mWorld.draw();
mWindow.setView(mWindow.getDefaultView());
mWindow.draw(mStatisticsText);
mWindow.display();
	*/
}

