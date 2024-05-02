#pragma once
#include<memory>
#include<vector>
#include<functional>
#include<SFML/Graphics.hpp>

namespace Category
{
	enum Type
	{
		None = 0,
		Scene = 1 << 0,
		PlayerAircraft = 1 << 1,
		AlliedAircraft = 1 << 2,
		EnemyAircraft = 1 << 3,
	};
}

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

	virtual unsigned int getCategory() const;
	void onCommand(const Command& command, sf::Time dt);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);

private:
	std::vector<Ptr> m_children;
	SceneNode* m_parent;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)>
derivedAction(Function fn)
{
	return [=](SceneNode& node, sf::Time dt)
	{
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);
		// Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}