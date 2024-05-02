#include "World.hpp"
#include "Stars.hpp"
#include <iostream>

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
	, mSpawnPosition(mWorldView.getSize().x / 2, mWorldView.getSize().y / 2)
	, mPlayerAircraft(nullptr)
{
	loadTextures();
	buildScene();
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	mPlayerAircraft->setVelocity(0.f, 0.f);

	sf::Vector2f velocity = mPlayerAircraft->getVelocity();
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
	mPlayerAircraft->setVelocity(mPlayerAircraft->getVelocity() + sf::Vector2f{0.f, mScrollSpeed});

	// Forward commands to the scene graph
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	mSceneGraph.update(dt);

	sf::FloatRect viewBounds(
		mWorldView.getCenter() - mWorldView.getSize() / 2.f,
		mWorldView.getSize());
	const float borderDistance = 40.f;
	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x,
		viewBounds.left + borderDistance);
	position.x = std::min(position.x,
		viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y,
		viewBounds.top + borderDistance);
	position.y = std::min(position.y,
		viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAircraft->setPosition(position);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
	mTextures.load(Textures::SpaceShip, "assets/SpaceShip.png");
	mTextures.load(Textures::Support, "assets/support.png");
	mTextures.load(Textures::Background, "assets/bg.png");
	mTextures.load(Textures::SmallStars, "assets/Stars-B.png");
	mTextures.load(Textures::BigStars, "assets/Stars-A.png");
	//mTextures.load(Textures::Projectile, "assets/rocket.png");
}

void World::buildScene()
{
	const float smallStarsSpeed = 15.f;
	const float bigStarsSpeed = 30.f;
	
	// crate scene layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

	// attach background
	sf::Texture& texture = mTextures.get(Textures::Background);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);// todo
	auto backgroundSprite = std::make_unique<SpriteNode>(texture, textureRect);
	backgroundSprite->setPosition(mWorldBounds.left,mWorldBounds.top);
	auto bgPtr = backgroundSprite.get();
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
	
	// attach small stars
	auto bgSmallStars = std::make_unique<Stars>(Textures::SmallStars, mTextures);
	bgSmallStars->setPosition(sf::Vector2f());
	bgSmallStars->setVelocity(0, smallStarsSpeed);
	bgPtr->attachChild(std::move(bgSmallStars));

	auto bgSmallStarsSecond = std::make_unique<Stars>(Textures::SmallStars, mTextures);
	bgSmallStarsSecond->setPosition(sf::Vector2f(0, -mWorldView.getSize().y));
	bgSmallStarsSecond->setVelocity(0, smallStarsSpeed);
	bgPtr->attachChild(std::move(bgSmallStarsSecond));

	// attach big stars
	auto bgBigStars = std::make_unique<Stars>(Textures::BigStars, mTextures);
	bgBigStars->setPosition(sf::Vector2f());
	bgBigStars->setVelocity(0, bigStarsSpeed);
	bgPtr->attachChild(std::move(bgBigStars));

	auto bgBigStarsSecond = std::make_unique<Stars>(Textures::BigStars, mTextures);
	bgBigStarsSecond->setPosition(sf::Vector2f(0, -mWorldView.getSize().y));
	bgBigStarsSecond->setVelocity(0, bigStarsSpeed);
	bgPtr->attachChild(std::move(bgBigStarsSecond));

	// attach aircraft
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::SpaceShip, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mPlayerAircraft->setScale(0.5, 0.5);
	mSceneLayers[Air]->attachChild(std::move(leader));

	// attach support
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Support, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}