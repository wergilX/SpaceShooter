#include "ParallelTask.hpp"

ParallelTask::ParallelTask()
{
}

void ParallelTask::execute()
{
}

bool ParallelTask::isFinished()
{
	sf::Lock lock(mMutex);
	return mFinished;
}

float ParallelTask::getCompletion()
{
	return 0.0f;
}

void ParallelTask::runTask()
{
	// Dummy task - stall 10 seconds
	bool ended = false;
	while (!ended)
	{
		sf::Lock lock(mMutex); // Protect the clock
		if (mElapsedTime.getElapsedTime().asSeconds() >= 10.f)
			ended = true;
	}
	{ // mFinished may be accessed from multiple threads, protect
		sf::Lock lock(mMutex);
		mFinished = true;
	}
}
