#pragma once
#include<SFML/Graphics.hpp>

#include"World.hpp"
#include"Player.hpp"

class Game
{
public:
	Game();
	void run();
private:
	void processEvents(sf::Event event);
	void update(sf::Time deltaTime);
	void render();

private:
	sf::RenderWindow m_window;
	std::unique_ptr<World> m_world;
	Player mPlayer;
	bool mIsPaused = true;
};

