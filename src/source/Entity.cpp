#include "stdHeader.hpp"

#include "Entity.hpp"

using namespace Entities;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Entity::Entity(sf::Texture& texture, 
			   const float& max_speed, const float& acceleration, const float& deceleration)
	: m_sprite           { new sf::Sprite(texture) },
	m_animation_component{ new Components::AnimationComponent(*m_sprite, texture) },
	m_movement_component { new Components::MovementComponent(*m_sprite, max_speed, acceleration, deceleration) }
{
}

Entity::~Entity()
{
	delete m_movement_component;
	delete m_animation_component;
	delete m_sprite;
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

void Entity::render(sf::RenderTarget* target)
{
	//target->draw(m_sprite);
	target->draw(*m_sprite);
}
