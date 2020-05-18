#include "stdHeader.hpp"

#include "Entity.hpp"

using namespace cog;

Entity::Entity() :
	m_shape{ sf::Vector2f(50.f, 50.f) },
	m_movement_speed{ 1000.f }
{
}

Entity::~Entity()
{

}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	m_shape.move(dir_x * m_movement_speed * dt, dir_y * m_movement_speed * dt);
}

void Entity::move(const float& dt, const sf::Vector2f& dir_vector_xy)
{
	m_shape.move(dir_vector_xy * m_movement_speed * dt);
}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(m_shape);
}
