#include "stdHeader.hpp"

#include "Tile.hpp"

//Constructors
Tile::Tile()
	: m_shape { sf::Vector2f(0.f, 0.f)}
{
}

Tile::Tile(const sf::Vector2f pos, const sf::Vector2f size_xy, const bool border_visible)
	: m_shape{ size_xy },
	m_border_visible { border_visible }
{
	m_shape.setPosition(pos);
	m_shape.setOutlineThickness(0.5f);

	if (border_visible == true)
		m_shape.setOutlineColor(sf::Color::Yellow);
	else
		m_shape.setOutlineColor(sf::Color::Transparent);

	m_shape.setFillColor(sf::Color::Transparent);
}

Tile::~Tile()
{

}

//Accessors
bool Tile::getBorberVisible() const
{
	return m_border_visible;
}

//Modificators
void Tile::setBorderVisible(const bool option)
{
	m_border_visible = option;

	if (option == true)
		m_shape.setOutlineColor(sf::Color::Yellow);
	else
		m_shape.setOutlineColor(sf::Color::Transparent);
}

//Update
void Tile::update(const float& dt)
{
}

//Render
void Tile::render(sf::RenderTarget& target)
{
	target.draw(m_shape);
}