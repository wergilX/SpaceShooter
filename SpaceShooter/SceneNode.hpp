#pragma once
#include<memory>
#include<vector>
#include<SFML/Graphics.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
public:
	SceneNode();
	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);

	void update(sf::Time dt);

	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);

private:
	std::vector<Ptr> m_chldren;
	SceneNode* m_parent;
};

