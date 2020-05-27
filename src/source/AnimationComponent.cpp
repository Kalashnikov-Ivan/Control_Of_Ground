#include "AnimationComponent.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Animation
////////////////////////////////////////////////////////////

//Constructors
AnimationComponent::Animation::Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, const float& animation_timer,
	sf::Vector2i& start_xy, sf::Vector2i& end_xy, sf::Vector2i& size_rect)
	: m_sprite       { sprite },
	m_texture_sheet  { texture_sheet },
	m_start_rect     { start_xy,  size_rect },
	m_current_rect   { m_start_rect },
	m_end_rect       { end_xy, size_rect },
	m_animation_timer{ animation_timer }, m_timer{ 0.f } //Timer
{
	m_sprite.setTexture(texture_sheet, true);
	m_sprite.setTextureRect(m_start_rect);
}

AnimationComponent::Animation::~Animation()
{
}


//Functions
void AnimationComponent::Animation::update(const float& dt)
{
	//Update timer
	m_timer = 10.f * dt;

	if (m_timer >= m_animation_timer)
	{
		//Reset timer
		m_timer = 0.f;

		//Animate
		if (m_current_rect != m_end_rect)
		{
			m_current_rect.left += m_size_rect.x;
		}
		else //Reset
		{
			m_current_rect.left = m_start_rect.left;
		}
	}
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

}

//Functions
void AnimationComponent::update(const float& dt)
{
}

void AnimationComponent::start_animation(const std::string& animation)
{
}
void AnimationComponent::pause_animation(const std::string& animation)
{
}
void AnimationComponent::reset_animation(const std::string& animation)
{
}