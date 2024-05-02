#include "LoadingState.hpp"

LoadingState::LoadingState()
{
	mLoadingText.setFont(font);
	mLoadingText.setString("Loading Resources");
	centerOrigin(mLoadingText);
	mLoadingText.setPosition(window.getSize().x / 2u, window.getSize().y /
		2u + 50);
	mProgressBarBackground.setFillColor(sf::Color::White);
	mProgressBarBackground.setSize(sf::Vector2f(window.getSize().x - 20,
		10));
	mProgressBarBackground.setPosition(10, mLoadingText.getPosition().y +
		40);
	mProgressBar.setFillColor(sf::Color(100, 100, 100));
	mProgressBar.setSize(sf::Vector2f(200, 10));
	mProgressBar.setPosition(10, mLoadingText.getPosition().y + 40);
	setCompletion(0.f);
	mLoadingTask.execute();

}

void LoadingState::setCompletion(float percent)
{
	if (percent > 1.f)
		percent = 1.f; // clamp
	mProgressBar.setSize(sf::Vector2f(
		mProgressBarBackground.getSize().x * percent,
		mProgressBar.getSize().y));
}

bool LoadingState::update(sf::Time)
{
	// Update the progress bar from the remote task or finish it
	if (mLoadingTask.isFinished())
	{
		requestStackPop();
		requestStackPush(States::Game);
	}
	else
	{
		setCompletion(mLoadingTask.getCompletion());
	}
	return true;
}