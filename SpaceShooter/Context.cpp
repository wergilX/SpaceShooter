#include "Context.hpp"

Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player) : 
	m_window(&window), m_textures(&textures), m_fonts(&fonts), m_player(&player)
{
}
