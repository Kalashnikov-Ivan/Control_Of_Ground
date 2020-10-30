#include "stdafx.h"

#include "AnimatedBackground.h"

using namespace GUI;

AnimatedBackground::AnimatedBackground(const sf::Vector2f& bgSize, sf::Texture& textureSheet)
	: m_background          { bgSize }
	, m_animationСomponent { m_background, textureSheet }
{
	//addAnimation (NAME, TIME_OF_ANIM (sec), START_X, START_Y, FRAMES_X, FRAMES_Y, WIDTH, HEIGHT)
	m_animationСomponent.AddAnimation("ANIMATION", 5.f, 0, 0, 13, 0, 1000, 600);
}

AnimatedBackground::~AnimatedBackground()
{

}

//Update
void AnimatedBackground::Update(const float& dt)
{
	m_animationСomponent.Play("ANIMATION", dt);
}

//Render
void AnimatedBackground::Render(sf::RenderTarget& target)
{
	target.draw(m_background);
}

void AnimatedBackground::Reset(const sf::VideoMode& vm)
{
	m_background.setSize(sf::Vector2f((float)(vm.width), (float)(vm.height)));
}