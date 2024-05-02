#include "PauseState.hpp"
#include <SFML/Graphics.hpp>

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(window.getSize()));
	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::BackSpace)
	{
		requestStateClear();
		requestStackPush(States::Menu);
	}

	return false;
}
