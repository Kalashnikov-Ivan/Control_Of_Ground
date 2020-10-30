#include "stdafx.h"

#include "RectAnimationComponent.h"

using namespace Components;

// Animation
////////////////////////////////////////////////////////////
//Constructors
RectAnimationComponent::Animation::Animation(sf::RectangleShape& shape, sf::Texture& textureSheet, const float& animationTimer,
	const int start_x, const int start_y, int frames_x, int frames_y,
	const int width, const int height)
	: m_shape        { shape }
	, m_textureSheet{ textureSheet }
	, m_width        { width }
	, m_height       { height }
	, m_startRect   { start_x * width, start_y * height, width, height }
	, m_currentRect { m_startRect }
	, m_endRect     { frames_x * width, frames_y * height, width, height }
	, m_animationTimer{ animationTimer }
	, m_timer{ 0.f }
	, m_isDone{ false } //Timer
{
	m_shape.setTexture(&textureSheet, true);
	m_shape.setTextureRect(m_startRect);
}

RectAnimationComponent::Animation::~Animation()
{
}

//Accessors
bool RectAnimationComponent::Animation::IsDone() const
{
	return m_isDone;
}


//Functions
bool RectAnimationComponent::Animation::Play(const float& dt, float modifPercent, const bool isPriority)
{
	if (modifPercent < 0.5f)
		modifPercent = 0.5f;

	m_isDone = false;
	//Update timer
	m_timer += modifPercent * 100.f * dt; //Old value: (modifier / max_modifier) * 100.f * dt

	if (m_timer >= m_animationTimer)
	{
		//Reset timer
		m_timer = 0.f;

		m_shape.setTextureRect(m_currentRect);

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

void RectAnimationComponent::Animation::Reset()
{
	m_timer = m_animationTimer;
	m_currentRect = m_startRect;
}

// RectAnimationComponent
////////////////////////////////////////////////////////////
//Constructors
RectAnimationComponent::RectAnimationComponent(sf::RectangleShape& shape, sf::Texture& textureSheet)
	: m_shape            { shape }
	, m_textureSheet     { textureSheet }
	, m_lastAnimation    { nullptr }
	, m_priorityAnimation{ nullptr }
{
}

RectAnimationComponent::~RectAnimationComponent()
{
	//Delete animations
	for (auto& i : m_animations)
		delete i.second;
}

//Accessors
bool Components::RectAnimationComponent::IsDone(const std::string& key)
{
	return m_animations[key]->IsDone();
}

//Functions
void RectAnimationComponent::AddAnimation(const std::string& key, const float& animation_timer,
	const int start_x, const int start_y, const int frames_x, const int frames_y,
	const int width, const int height)
{
	m_animations[key] = new Animation{ m_shape, m_textureSheet, animation_timer, start_x, start_y, frames_x, frames_y, width, height };
}

bool RectAnimationComponent::Play(const std::string& key, const float& dt, const float& modifier, const float& max_modifier, const bool is_priority)
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

			if (m_animations[key]->Play(dt, abs(modifier / max_modifier)))
				m_priorityAnimation = nullptr;
		}
	}
	else
	{
		if (is_priority)
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

		m_animations[key]->Play(dt, abs(modifier / max_modifier));
	}

	return m_animations[key]->IsDone();
}