#ifndef ANIMATED_BACKGROUND_H
#define ANIMATED_BACKGROUND_H

#include "RectAnimationComponent.h"

namespace GUI
{
class AnimatedBackground
{
public:
	AnimatedBackground(const sf::Vector2f& bgSize, sf::Texture& textureSheet);
	~AnimatedBackground();

	//Functions
	void Update(const float& dt);

	void Render(sf::RenderTarget& target);

	void Reset(const sf::VideoMode& vm);

private:
	sf::RectangleShape m_background;

	Components::RectAnimationComponent m_animationСomponent;
};
} // !namespace GUI
#endif // !ANIMATED_BACKGROUND_H