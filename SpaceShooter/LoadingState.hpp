#pragma once
#include"ParallelTask.hpp"
#include<SFML/Graphics.hpp>

class LoadingState
{
public:
	LoadingState();
	void setCompletion(float percent);
	bool update(sf::Time);
private:
	sf::Text mLoadingText;
	sf::RectangleShape mProgressBarBackground;
	sf::RectangleShape mProgressBar;
	ParallelTask mLoadingTask;
};

