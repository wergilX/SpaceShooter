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
	/*mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();
	if (position.x <= mWorldBounds.left + 150
		|| position.x >= mWorldBounds.left + mWorldBounds.width - 150)
	{
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}*/
	mSceneGraph.update(dt);
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
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left,mWorldBounds.top);
	auto bgPtr = backgroundSprite.get();
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
	
	//// attach BigStars
	//sf::Texture& textureBigStars = mTextures.get(Textures::BigStars);
	//sf::IntRect textureRectBigStars(mWorldBounds);
	//std::unique_ptr<SpriteNode> backgroundBigStarsSprite(new SpriteNode(textureBigStars, textureRectBigStars));
	//backgroundBigStarsSprite->setPosition(mWorldBounds.left,mWorldBounds.top);
	//auto smallStarPtr = backgroundBigStarsSprite.get();
	//bgPtr->attachChild(std::move(backgroundBigStarsSprite));

	//// attach SmallStars
	//sf::Texture& textureSmallStars = mTextures.get(Textures::SmallStars);
	//sf::IntRect textureRectSmallStars(mWorldBounds);
	//std::unique_ptr<SpriteNode> backgroundSmallStarsSprite(new SpriteNode(textureSmallStars, textureRectSmallStars));
	//backgroundSmallStarsSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	//smallStarPtr->attachChild(std::move(backgroundSmallStarsSprite));

	std::unique_ptr<Stars> bgSmallStars(new Stars(Textures::SmallStars, mTextures));
	bgSmallStars->setPosition(sf::Vector2f());
	bgSmallStars->setVelocity(0, 10.55f);
	auto smallStarsPtr = bgSmallStars.get();
	bgPtr->attachChild(std::move(bgSmallStars));

	// attach aircraft
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::SpaceShip, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));

	// attach support
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Support, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

}
