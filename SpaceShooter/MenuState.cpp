#include "MenuState.hpp"

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
	, mGUIContainer()
{
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(playOption);

	...
		auto playButton = std::make_shared<GUI::Button>(
			*context.fonts, *context.textures);
	playButton->setPosition(100, 250);
	playButton->setText("Play");
	playButton->setCallback([this]()
		{
			requestStackPop();
			requestStackPush(States::Game);
		});
	mGUIContainer.pack(playButton);
}

void MenuState::updateOptionText()
{
	if (mOptions.empty())
		return;
	// White all texts
	for (sf::Text& text : mOptions)
		text.setColor(sf::Color::White);
	// Red the selected text
	mOptions[mOptionIndex].setColor(sf::Color::Red);
}

void MenuState::handleEvent()
{
	//todo set event

	sf::Event event;

	if (event.key.code == sf::Keyboard::Up)
	{
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;
		updateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;
		updateOptionText();
	}

	if (event.key.code == sf::Keyboard::Return)
	{
		if (mOptionIndex == Play)
		{
			requestStackPop();
			requestStackPush(States::Game);
		}
		else if (mOptionIndex == Exit)
		{
			requestStackPop();
		}
	}


	void MenuState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());
		window.draw(mBackgroundSprite);
		window.draw(mGUIContainer);
	}
	bool MenuState::update(sf::Time)
	{
		return true;
	}
	bool MenuState::handleEvent(const sf::Event & event)
	{
		mGUIContainer.handleEvent(event);
		return false;
	}
}

