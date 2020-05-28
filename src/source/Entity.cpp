#include "stdHeader.hpp"

#include "Entity.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Entity::Entity(sf::Texture& texture, 
			   const float& max_speed, const float& acceleration, const float& deceleration)
	: m_sprite           { new sf::Sprite(texture) },
	m_animation_component{ new AnimationComponent(*m_sprite, texture) },
	m_movement_component { new MovementComponent(*m_sprite, max_speed, acceleration, deceleration) }
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
sf::Vector2f Entity::get_speed() const
{
	if (m_movement_component != nullptr)
		return m_movement_component->get_speed();
	else
		return sf::Vector2f(0.f, 0.f);
}


////////////////////////////////////////////////////////////
// Modifiers
////////////////////////////////////////////////////////////
void Entity::set_position(const sf::Vector2f& position_xy)
{
	//m_sprite.setPosition(position_xy);
	m_sprite->setPosition(position_xy);
}

void Entity::set_texture(const sf::Texture& texture)
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
