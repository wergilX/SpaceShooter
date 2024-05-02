#pragma once

#include<functional>
#include<SFML/Graphics.hpp>

class SceneNode;

struct Command
{
	Command();
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};
