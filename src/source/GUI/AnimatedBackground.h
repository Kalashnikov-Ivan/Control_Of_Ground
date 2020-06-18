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

	//Functions
	void update(const float& dt);

	void render(sf::RenderTarget& target);

	void reset(const sf::VideoMode& vm);

private:
	sf::RectangleShape m_background;

	Components::RectAnimationComponent m_animation_component;
};
} // !namespace GUI
#endif // !ANIMATED_BACKGROUND_H