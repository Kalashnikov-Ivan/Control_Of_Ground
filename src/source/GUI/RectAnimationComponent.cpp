#include "stdHeader.hpp"

#include "RectAnimationComponent.h"

using namespace Components;

////////////////////////////////////////////////////////////
// Animation
////////////////////////////////////////////////////////////

//Constructors
RectAnimationComponent::Animation::Animation(sf::RectangleShape& shape, sf::Texture& texture_sheet, const float& animation_timer,
	const int start_x, const int start_y, int frames_x, int frames_y,
	const int width, const int height)
	: m_shape{ shape },
	m_texture_sheet{ texture_sheet },
	m_width{ width }, m_height{ height },
	m_start_rect{ start_x * width, start_y * height, width, height },
	m_current_rect{ m_start_rect },
	m_end_rect{ frames_x * width, frames_y * height, width, height },
	m_animation_timer{ animation_timer }, m_timer{ 0.f }, m_is_done{ false } //Timer
{
	m_shape.setTexture(&texture_sheet, true);
	m_shape.setTextureRect(m_start_rect);
}

RectAnimationComponent::Animation::~Animation()
{
}

//Accessors
bool RectAnimationComponent::Animation::isDone() const
{
	return m_is_done;
}


//Functions
bool RectAnimationComponent::Animation::play(const float& dt, float modif_percent, const bool is_priority)
{
	if (modif_percent < 0.5f)
		modif_percent = 0.5f;

	m_is_done = false;
	//Update timer
	m_timer += modif_percent * 100.f * dt; //Old value: (modifier / max_modifier) * 100.f * dt

	if (m_timer >= m_animation_timer)
	{
		//Reset timer
		m_timer = 0.f;

		m_shape.setTextureRect(m_current_rect);

		//Animate
		if (m_current_rect != m_end_rect)
		{
			m_current_rect.left += m_width;
		}
		else //Reset
		{
			m_current_rect.left = m_start_rect.left;
			m_is_done = true;
		}
	}

	return m_is_done;
}

void RectAnimationComponent::Animation::reset()
{
	m_timer = m_animation_timer;
	m_current_rect = m_start_rect;
}

//------------------------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////
// RectAnimationComponent
////////////////////////////////////////////////////////////

//Constructors
RectAnimationComponent::RectAnimationComponent(sf::RectangleShape& shape, sf::Texture& texture_sheet)
	: m_shape{ shape },
	m_texture_sheet{ texture_sheet },
	m_last_animation{ nullptr }, m_priority_animation{ nullptr }
{
}

RectAnimationComponent::~RectAnimationComponent()
{
	//Delete animations
	for (auto& i : m_animations)
		delete i.second;
}

//Accessors
bool Components::RectAnimationComponent::isDone(const std::string& key)
{
	return m_animations[key]->isDone();
}

//Functions
void RectAnimationComponent::addAnimation(const std::string& key, const float& animation_timer,
	const int start_x, const int start_y, const int frames_x, const int frames_y,
	const int width, const int height)
{
	m_animations[key] = new Animation{ m_shape, m_texture_sheet, animation_timer, start_x, start_y, frames_x, frames_y, width, height };
}

bool RectAnimationComponent::play(const std::string& key, const float& dt, const float& modifier, const float& max_modifier, const bool is_priority)
{
	if (m_priority_animation)
	{
		if (m_priority_animation == m_animations[key])
		{
			if (m_last_animation != m_animations[key])
			{
				if (m_last_animation == nullptr)
					m_last_animation = m_animations[key];
				else
				{
					m_last_animation->reset();
					m_last_animation = m_animations[key];
				}
			}

			if (m_animations[key]->play(dt, abs(modifier / max_modifier)))
				m_priority_animation = nullptr;
		}
	}
	else
	{
		if (is_priority)
			m_priority_animation = m_animations[key];

		if (m_last_animation != m_animations[key])
		{
			if (m_last_animation == nullptr)
				m_last_animation = m_animations[key];
			else
			{
				m_last_animation->reset();
				m_last_animation = m_animations[key];
			}
		}

		m_animations[key]->play(dt, abs(modifier / max_modifier));
	}

	return m_animations[key]->isDone();
}