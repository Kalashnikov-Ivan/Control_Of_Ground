#ifndef ANIMATED_BACKGROUND_H
#define ANIMATED_BACKGROUND_H

#include "RectAnimationComponent.h"

namespace GUI
{
class AnimatedBackground
{
public:
	AnimatedBackground(const sf::Vector2f& bg_size, sf::Texture& texture_sheet);
	~AnimatedBackground();

	//Update
	void update(const float& dt);

	//Render
	void render(sf::RenderTarget& target);

private:
	sf::RectangleShape m_background;

	Components::RectAnimationComponent m_animation_component;
};
} // !namespace GUI
#endif // !ANIMATED_BACKGROUND_H