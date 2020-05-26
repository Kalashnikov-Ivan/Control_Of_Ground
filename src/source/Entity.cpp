#include "stdHeader.hpp"

#include "Entity.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Entity::Entity(sf::Texture& texture, const float& max_speed, float acceleration, float deceleration)
	: m_sprite{ new sf::Sprite(texture)},
	m_movement_component{ new MovementComponent(*m_sprite, max_speed, acceleration, deceleration) }
{
}

Entity::~Entity()
{
	delete m_sprite;
	delete m_movement_component;
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////

void Entity::set_texture(sf::Texture* texture)
{
	//m_sprite.setTexture(*texture);
	m_sprite->setTexture(*texture);
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////

void Entity::move(const sf::Vector2f& dir_xy, const float& dt)
{
	m_movement_component->move(dir_xy, dt);
}

//Modifiers
void Entity::set_position(const sf::Vector2f& position_xy)
{
	//m_sprite.setPosition(position_xy);
	m_sprite->setPosition(position_xy);
}

//Virtual
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
