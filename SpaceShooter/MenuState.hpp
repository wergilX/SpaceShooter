#pragma once
#include<vector>
#include<SFML/Graphics.hpp>

enum OptionNames
{
	Play,
	Exit,
};

class MenuState
{
public:
	MenuState(StateStack& stack, Context context);
	void updateOptionText();
	void handleEvent();
	void draw();
	bool update(sf::Time);
	bool handleEvent(const sf::Event& event);

private:
	std::vector<sf::Text> mOptions;
	std::size_t mOptionIndex;
};

