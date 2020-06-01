#include "HitboxComponent.hpp"

using namespace Components;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
HitboxComponent::HitboxComponent(sf::Sprite& sprite,
								 const sf::Vector2f& offset_basic,
								 const sf::Vector2f& size_xy,
								 const sf::Vector2f& scale)
	: m_sprite{ sprite },
	m_offset_basic{ offset_basic }, m_offset_move{ sf::Vector2f(0.f, 0.f) },
	m_hitbox{ size_xy }
{
	m_hitbox.setPosition(m_sprite.getPosition() + m_offset_basic);
	m_hitbox.setScale(scale);

	//Debug
	m_hitbox.setFillColor(sf::Color::Transparent);
	m_hitbox.setOutlineThickness(0.5f);
	m_hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

////////////////////////////////////////////////////////////
// Modificators
////////////////////////////////////////////////////////////
void HitboxComponent::setOffsetMove(const sf::Vector2f& offset)
{
	m_offset_move = offset;
}

void HitboxComponent::setRotation(const float& rotation)
{
	m_hitbox.setRotation(rotation);
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
bool HitboxComponent::checkIntersect(const sf::FloatRect& f_rect)
{
	return m_hitbox.getGlobalBounds().intersects(f_rect);
}

void HitboxComponent::update(const float& dt)
{
	m_hitbox.setPosition(m_sprite.getPosition() + m_offset_basic + m_offset_move);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(m_hitbox);
}
