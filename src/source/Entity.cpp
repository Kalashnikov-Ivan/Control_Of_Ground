#include "stdHeader.hpp"

#include "Entity.hpp"

using namespace Entities;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Entity::Entity(sf::Texture& texture)
	: m_sprite           { new sf::Sprite(texture) },
	m_movement_component { nullptr }, 
	m_animation_component{ nullptr },
	m_hitbox_component   { nullptr }
{
}

Entity::~Entity()
{
	/*??? Idea: put possession of components (delete heap memory) in children classes ???*/

	if (m_hitbox_component)
		delete m_hitbox_component;
	if (m_movement_component)
		delete m_movement_component;
	if (m_animation_component)
		delete m_animation_component;

	delete m_sprite;
}

////////////////////////////////////////////////////////////
// Creators
////////////////////////////////////////////////////////////
void Entity::createMovementComponent(sf::Sprite& sprite, const float& max_speed, const float& acceleration, const float& deceleration)
{
	m_movement_component = new Components::MovementComponent(sprite, max_speed, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
{
	m_animation_component = new Components::AnimationComponent(sprite, texture_sheet);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, const sf::Vector2f& offset_xy, const sf::Vector2f& size_xy)
{
	m_hitbox_component = new Components::HitboxComponent(sprite, offset_xy, size_xy);
}


////////////////////////////////////////////////////////////
// Modifiers
////////////////////////////////////////////////////////////
//Accessors
sf::Vector2f Entity::getSpeed() const
{
	if (m_movement_component != nullptr)
		return m_movement_component->getSpeed();
	else
		return sf::Vector2f(0.f, 0.f);
}


////////////////////////////////////////////////////////////
// Modifiers
////////////////////////////////////////////////////////////
void Entity::setPosition(const sf::Vector2f& position_xy)
{
	//m_sprite.setPosition(position_xy);
	m_sprite->setPosition(position_xy);
}

void Entity::setTexture(const sf::Texture& texture)
{
	//m_sprite.setTexture(*texture);
	m_sprite->setTexture(texture);
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
void Entity::move(const sf::Vector2f& dir_xy, const float& dt)
{
	m_movement_component->move(dir_xy, dt);
}

////////////////////////////////////////////////////////////
// Virtual
////////////////////////////////////////////////////////////
void Entity::update(const float& dt)
{
	if (m_movement_component != nullptr)
	{
		m_movement_component->update(dt);
	}
}

void Entity::render(sf::RenderTarget& target)
{
	//target->draw(m_sprite);
	target.draw(*m_sprite);
}
