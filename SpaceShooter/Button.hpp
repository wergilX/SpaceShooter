#pragma once
#include <SFML/Graphics.hpp>

namespace GUI
{
	class Button
	{
	public:

		Button(const FontHolder& fonts, const TextureHolder& textures);

		bool isSelectable() const;
		void select();
		void deselect();
		void activate();
		void deactivate();
	};
}