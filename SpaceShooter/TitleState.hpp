#pragma once
#include"State.hpp"
#include"StateStack.hpp"
#include"Context.hpp"

class TitleState : public State
{
public:
	TitleState(StateStack& stack,
		Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
private:
	sf::Sprite mBackgroundSprite;
	sf::Text mText;
	bool mShowText;
	sf::Time mTextEffectTime;
};
