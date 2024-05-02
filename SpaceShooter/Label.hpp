#pragma once
#include <SFML/Graphics.hpp>

namespace GUI
{
	class Label
	{
	public:
		Label(const std::string& text, const FontHolder& fonts);
		bool Label::isSelectable() const;
		void Label::draw(sf::RenderTarget& target, sf::RenderStates states)const;
		void Label::setText(const std::string& text);
	};
}
