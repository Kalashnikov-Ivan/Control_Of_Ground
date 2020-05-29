#include "AnimationComponent.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Animation
////////////////////////////////////////////////////////////

//Constructors
AnimationComponent::Animation::Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, const float& animation_timer,
										 const int start_x, const int start_y, int frames_x, int frames_y,
										 const int width, const int height)
	: m_sprite       { sprite },
	m_texture_sheet  { texture_sheet },
	m_width          { width }, m_height{ height },
	m_start_rect     { start_x * width, start_y * height, width, height },
	m_current_rect   { m_start_rect },
	m_end_rect       { frames_x * width, frames_y * height, width, height },
	m_animation_timer{ animation_timer }, m_timer{ 0.f } //Timer
{
	m_sprite.setTexture(texture_sheet, true);
	m_sprite.setTextureRect(m_start_rect);
}

AnimationComponent::Animation::~Animation()
{
}


//Functions
void AnimationComponent::Animation::play(const float& dt)
{
	//Update timer
	m_timer += dt; //Old value: 100.f * dt

	if (m_timer >= m_animation_timer)
	{
		//Reset timer
		m_timer = 0.f;

		//Animate
		if (m_current_rect != m_end_rect)
		{
			m_current_rect.left += m_width;
		}
		else //Reset
		{
			m_current_rect.left = m_start_rect.left;
		}

		m_sprite.setTextureRect(m_current_rect);
	}
}

void AnimationComponent::Animation::reset()
{

}

////////////////////////////////////////////////////////////
// AnimationComponent
////////////////////////////////////////////////////////////

//Constructors
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	: m_sprite{ sprite },
	m_texture_sheet{ texture_sheet }
{
}

AnimationComponent::~AnimationComponent()
{
	//Delete animations
	for (auto& i : m_animations)
		delete i.second;
}

//Functions
void AnimationComponent::addAnimation(const std::string& key, const float& animation_timer,
							const int start_x, const int start_y, const int frames_x, const int frames_y,
							const int width, const int height)
{
	m_animations[key] = new Animation{ m_sprite, m_texture_sheet, animation_timer, start_x, start_y, frames_x, frames_y, width, height };
}

void AnimationComponent::play(const std::string& key, const float& dt)
{
	m_animations[key]->play(dt);
}