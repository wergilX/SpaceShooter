#pragma once
#include<SFML/Graphics.hpp>
#include"ResourceHolder.hpp"
#include"Player.hpp"


struct Context
{
	Context(sf::RenderWindow& window,
		TextureHolder& textures,
		FontHolder& fonts,
		Player& player);
	sf::RenderWindow* m_window;
	TextureHolder* m_textures;
	FontHolder* m_fonts;
	Player* m_player;
};

