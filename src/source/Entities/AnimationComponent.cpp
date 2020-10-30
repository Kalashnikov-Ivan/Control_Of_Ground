#include "stdafx.h"

#include "AnimationComponent.hpp"

using namespace Components;

////////////////////////////////////////////////////////////
// Animation
////////////////////////////////////////////////////////////

//Constructors
AnimationComponent::Animation::Animation(sf::Sprite& sprite, sf::Texture& textureSheet, const float& animation_timer,
										 const int start_x, const int start_y, int frames_x, int frames_y,
										 const int width, const int height)
	: m_sprite       { sprite },
	m_textureSheet  { textureSheet },
	m_width          { width }, m_height{ height },
	m_startRect     { start_x * width, start_y * height, width, height },
	m_currentRect   { m_startRect },
	m_endRect       { frames_x * width, frames_y * height, width, height },
	m_animationTimer{ animation_timer }, m_timer{ 0.f }, m_isDone{ false } //Timer
{
	m_sprite.setTexture(textureSheet, true);
	m_sprite.setTextureRect(m_startRect);
}

AnimationComponent::Animation::~Animation()
{
}

//Accessors
bool AnimationComponent::Animation::IsDone() const
{
	return m_isDone;
}


//Functions
bool AnimationComponent::Animation::Play(const float& dt, float modif_percent, const bool is_priority)
{
	if (modif_percent < 0.5f)
		modif_percent = 0.5f;

	m_isDone = false;
	//Update timer
	m_timer += modif_percent * 100.f * dt; //Old value: (modifier / max_modifier) * 100.f * dt

	if (m_timer >= m_animationTimer)
	{
		//Reset timer
		m_timer = 0.f;

		m_sprite.setTextureRect(m_currentRect);

		//Animate
		if (m_currentRect != m_endRect)
		{
			m_currentRect.left += m_width;
		}
		else //Reset
		{
			m_currentRect.left = m_startRect.left;
			m_isDone = true;
		}
	}

	return m_isDone;
}

void AnimationComponent::Animation::Reset()
{
	m_timer = m_animationTimer;
	m_currentRect = m_startRect;
}

// AnimationComponent
////////////////////////////////////////////////////////////
//Constructors
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	: m_sprite{ sprite },
	m_textureSheet{ textureSheet },
	m_lastAnimation{ nullptr }, m_priorityAnimation{ nullptr }
{
}

AnimationComponent::~AnimationComponent()
{
	//Delete animations
	for (auto& i : m_animations)
		delete i.second;
}

//Accessors
bool Components::AnimationComponent::IsDone(const std::string& key)
{
	return m_animations[key]->IsDone();
}

//Functions
void AnimationComponent::AddAnimation(const std::string& key, const float& animationTimer,
							const int start_x, const int start_y, const int frames_x, const int frames_y,
							const int width, const int height)
{
	m_animations[key] = new Animation{ m_sprite, m_textureSheet, animationTimer, start_x, start_y, frames_x, frames_y, width, height };
}

bool AnimationComponent::Play(const std::string& key, const float& dt, const float& modifier, const float& maxModifier, const bool isPriority)
{
	if (m_priorityAnimation)
	{
		if (m_priorityAnimation == m_animations[key])
		{
			if (m_lastAnimation != m_animations[key])
			{
				if (m_lastAnimation == nullptr)
					m_lastAnimation = m_animations[key];
				else
				{
					m_lastAnimation->Reset();
					m_lastAnimation = m_animations[key];
				}
			}

			if (m_animations[key]->Play(dt, abs(modifier / maxModifier)))
				m_priorityAnimation = nullptr;
		}
	}
	else
	{
		if (isPriority)
			m_priorityAnimation = m_animations[key];

		if (m_lastAnimation != m_animations[key])
		{
			if (m_lastAnimation == nullptr)
				m_lastAnimation = m_animations[key];
			else
			{
				m_lastAnimation->Reset();
				m_lastAnimation = m_animations[key];
			}
		}

		m_animations[key]->Play(dt, abs(modifier / maxModifier));
	}

	return m_animations[key]->IsDone();
}