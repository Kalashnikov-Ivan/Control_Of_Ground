#include "stdafx.h"

#include "Entity.hpp"

using namespace Entities;
using namespace Components;

// Constructors
Entity::Entity(sf::Texture& texture, const sf::Vector2f& scale)
	: m_sprite            { texture }
	, m_movementСomponent { nullptr }
	, m_animationСomponent{ nullptr }
	, m_hitboxComponent   { nullptr }
{
	m_sprite.setScale(scale);
}

Entity::~Entity()
{
}

// Creators
void Entity::createMovementComponent(sf::Sprite& sprite, const float& maxSpeed, const float& acceleration, const float& deceleration)
{
	m_movementСomponent = std::make_unique<MovementComponent>(sprite, maxSpeed, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
{
	m_animationСomponent = std::make_unique<AnimationComponent>(sprite, textureSheet);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, const sf::Vector2f& offset_xy, const sf::Vector2f& size_xy, const sf::Vector2f& scale)
{
	m_hitboxComponent = std::make_unique<HitboxComponent>(sprite, offset_xy, size_xy, scale);
}

// Accessors
const sf::Vector2f Entity::GetSpeed() const
{
	if (m_movementСomponent != nullptr)
		return m_movementСomponent->GetSpeed();
	else
		return sf::Vector2f(0.f, 0.f);
}

const sf::Vector2f Entity::GetSpeedDir() const
{
	if (m_movementСomponent != nullptr)
		return m_movementСomponent->GetSpeedDir();
	else
		return sf::Vector2f(0.f, 0.f);
}

// Modifiers
void Entity::SetPosition(const sf::Vector2f& position_xy)
{
	//m_sprite.setPosition(position_xy);
	m_sprite.setPosition(position_xy);
}

void Entity::SetTexture(const sf::Texture& texture)
{
	//m_sprite.setTexture(*texture);
	m_sprite.setTexture(texture);
}