#pragma once
#include <SFML/Graphics.hpp>

namespace GUI
{
	class Container
	{
	public:
		Container();

		void pack(Component::Ptr component);

		bool isSelectable() const;

		void handleEvent(const sf::Event& event);

		void select(std::size_t index);

		void selectNext();

		void selectPrevious();
	};

}