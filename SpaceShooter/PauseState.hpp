#pragma once
#include"State.hpp"
#include"StateStack.hpp"
#include"Context.hpp"

class PauseState : public State
{
public:
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
private:
	std::string mPausedText = "PAUSE";
	std::string mInstructionText = "PRESS ENTER";
};

