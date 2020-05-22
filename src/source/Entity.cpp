#include "stdHeader.hpp"

#include "Entity.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Entity::Entity(sf::Texture* texture, const float& max_speed)
	: m_sprite{ new sf::Sprite(*texture)},
	m_movement_component{ new MovementComponent(*m_sprite, max_speed) }
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

void Entity::move(const float& dt, const sf::Vector2f& dir_xy)
{
	//m_sprite.move(dir_vector_xy * m_movement_speed * dt);
	m_movement_component->move(dir_xy, dt);
	m_sprite->move(m_movement_component->get_speed() * dt);
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
}

void Entity::render(sf::RenderTarget* target)
{
	//target->draw(m_sprite);
	target->draw(*m_sprite);
}
