#include "stdafx.h"

#include "HitboxComponent.hpp"

using namespace Components;

//Constructors
HitboxComponent::HitboxComponent(sf::Sprite& sprite,
								 const sf::Vector2f& offsetBasic,
								 const sf::Vector2f& size_xy,
								 const sf::Vector2f& scale)
	: m_sprite     { sprite }
	, m_offsetBasic{ offsetBasic }
	, m_offsetMove { sf::Vector2f(0.f, 0.f) }
	, m_hitbox     { size_xy }
	, m_defaultSize{ size_xy }
{
	m_hitbox.setPosition(m_sprite.getPosition() + m_offsetBasic);
	m_hitbox.setScale(scale);

	//Debug
	m_hitbox.setFillColor(sf::Color::Transparent);
	m_hitbox.setOutlineThickness(0.3f);
	m_hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

// Accessors
sf::Vector2f HitboxComponent::GetDefaultSize() const
{
	return m_defaultSize;
}

// Modificators
void HitboxComponent::SetPosition(const sf::Vector2f& position)
{
	m_hitbox.setPosition(position + m_offsetBasic);
}


void HitboxComponent::SetOffsetMove(const sf::Vector2f& offset)
{
	m_offsetMove = offset;
}

void HitboxComponent::SetRotation(const float& rotation)
{
	m_hitbox.setRotation(rotation);
}

void Components::HitboxComponent::SetSize(const sf::Vector2f& size)
{
	m_hitbox.setSize(size);
}

//Functions
bool HitboxComponent::СheckIntersect(const sf::FloatRect& f_rect)
{
	return m_hitbox.getGlobalBounds().intersects(f_rect);
}

//Update and Render
void HitboxComponent::Update(const float& dt)
{
	m_hitbox.setPosition(m_sprite.getPosition() + m_offsetBasic + m_offsetMove);
}

void HitboxComponent::Render(sf::RenderTarget& target)
{
	target.draw(m_hitbox);
}
