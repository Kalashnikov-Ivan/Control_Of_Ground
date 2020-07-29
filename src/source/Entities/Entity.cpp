#include "stdHeader.hpp"

#include "Entity.hpp"

using namespace Entities;
using namespace Components;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Entity::Entity(sf::Texture& texture, const sf::Vector2f& scale)
	: m_sprite           { texture },
	mPtr_movement_component { nullptr }, 
	mPtr_animation_component{ nullptr },
	mPtr_hitbox_component   { nullptr }
{
	m_sprite.setScale(scale);
}

Entity::~Entity()
{
}

////////////////////////////////////////////////////////////
// Creators
////////////////////////////////////////////////////////////
void Entity::createMovementComponent(sf::Sprite& sprite, const float& max_speed, const float& acceleration, const float& deceleration)
{
	mPtr_movement_component = std::make_unique<MovementComponent>(sprite, max_speed, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
{
	mPtr_animation_component = std::make_unique<AnimationComponent>(sprite, texture_sheet);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, const sf::Vector2f& offset_xy, const sf::Vector2f& size_xy, const sf::Vector2f& scale)
{
	mPtr_hitbox_component = std::make_unique<HitboxComponent>(sprite, offset_xy, size_xy, scale);
}


////////////////////////////////////////////////////////////
// Accessors
////////////////////////////////////////////////////////////
const sf::Vector2f Entity::getSpeed() const
{
	if (mPtr_movement_component != nullptr)
		return mPtr_movement_component->getSpeed();
	else
		return sf::Vector2f(0.f, 0.f);
}

const sf::Vector2f Entity::getSpeedDir() const
{
	if (mPtr_movement_component != nullptr)
		return mPtr_movement_component->getSpeedDir();
	else
		return sf::Vector2f(0.f, 0.f);
}

////////////////////////////////////////////////////////////
// Modifiers
////////////////////////////////////////////////////////////
void Entity::setPosition(const sf::Vector2f& position_xy)
{
	//m_sprite.setPosition(position_xy);
	m_sprite.setPosition(position_xy);
}

void Entity::setTexture(const sf::Texture& texture)
{
	//m_sprite.setTexture(*texture);
	m_sprite.setTexture(texture);
}