#include "SceneNode.hpp"
#include<cassert>

SceneNode::SceneNode()
{
}

void SceneNode::attachChild(Ptr child)
{
	child->m_parent = this;
	m_chldren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(m_chldren.begin(), m_chldren.end(), [&](Ptr& p) -> bool
		{ return p.get() == &node; });
	
	assert(found != m_chldren.end());

	Ptr result = std::move(*found);
	result->m_parent = nullptr;
	m_chldren.erase(found);

	return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);

	for (const Ptr& child : m_chldren)
	{
		child->draw(target, states);
	}
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt)
{
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (Ptr& child : m_chldren)
		child->update(dt);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this;
		node != nullptr; node = node->m_parent)
		transform = node->getTransform() * transform;
	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}