#include "stdHeader.hpp"

#include "Entity.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Entity::Entity(sf::Texture* texture)
	: m_texture(texture),
	m_sprite{ new sf::Sprite(*texture) },
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

void Entity::move(const float& dt, const sf::Vector2f& dir_vector_xy)
{
	if (m_sprite)
	{
		m_sprite->move(dir_vector_xy * m_movement_speed * dt);
	}
}

//Modifiers
void Entity::set_position(const sf::Vector2f& position_xy)
{
	m_sprite->setPosition(position_xy);
}

//Virtual
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
