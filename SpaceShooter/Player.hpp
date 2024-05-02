#pragma once
#include"CommandQueue.hpp"

class Player
{
public:
	Player();
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);

public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown
	};
	void assignKey(Action action, sf::Keyboard::Key key);

	sf::Keyboard::Key getAssignedKey(Action action) const;
private:
	static bool isRealtimeAction(Action action);
private:
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command> mActionBinding;

};
