#include "stdHeader.hpp"

#include "Entity.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Entity::Entity() 
	: m_shape{ sf::Vector2f(50.f, 50.f) },
	m_movement_speed{ 1000.f }
{
}

Entity::~Entity()
{
	delete m_sprite;
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	if (m_sprite)
	{
		m_sprite->move(dir_x * m_movement_speed * dt, dir_y * m_movement_speed * dt);
	}
}

void Entity::move(const float& dt, const sf::Vector2f& dir_vector_xy)
{
	if (m_sprite)
	{
		m_sprite->move(dir_vector_xy * m_movement_speed * dt);
	}
}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget* target)
{
	if (m_sprite)
	{
		target->draw(*m_sprite);
	}
}
