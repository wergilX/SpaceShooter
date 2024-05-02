#include "Button.hpp"

Button::Button(const FontHolder& fonts, const TextureHolder& textures)
// ...
{
	mSprite.setTexture(mNormalTexture);
	mText.setPosition(sf::Vector2f(mNormalTexture.getSize() / 2u));
}

bool Button::isSelectable() const
{
	return true;
}

void Button::select()
{
	Component::select();
	mSprite.setTexture(mSelectedTexture);
}
void Button::deselect()
{
	Component::deselect();
	mSprite.setTexture(mNormalTexture);
}
void Button::activate()
{
	Component::activate();
	if (mIsToggle)
		mSprite.setTexture(mPressedTexture);
	if (mCallback)
		mCallback();
	if (!mIsToggle)
		deactivate();
}
void Button::deactivate()
{
	Component::deactivate();
	if (mIsToggle)
	{
		if (isSelected())
			mSprite.setTexture(mSelectedTexture);
		else
			mSprite.setTexture(mNormalTexture);
	}
}