#include "stdHeader.hpp"

#include "AnimatedBackground.h"

using namespace GUI;

AnimatedBackground::AnimatedBackground(const sf::Vector2f& bg_size, sf::Texture& texture_sheet)
	: m_background { bg_size },
	m_animation_component { m_background, texture_sheet }
{
	//addAnimation (NAME, TIME_OF_ANIM (sec), START_X, START_Y, FRAMES_X, FRAMES_Y, WIDTH, HEIGHT)
	m_animation_component.addAnimation("ANIMATION", 5.f, 0, 0, 13, 0, 1000, 600);
}

AnimatedBackground::~AnimatedBackground()
{

}

//Update
void AnimatedBackground::update(const float& dt)
{
	m_animation_component.play("ANIMATION", dt);
}

//Render
void AnimatedBackground::render(sf::RenderTarget& target)
{
	target.draw(m_background);
}
