#include "stdHeader.hpp"

#include "Tile.hpp"

//Constructors
Tile::Tile()
	: m_shape { sf::Vector2f(0.f, 0.f)}
{
}

Tile::Tile(const sf::Vector2f pos, const sf::Vector2f size_xy)
	: m_shape{ size_xy }
{
	m_shape.setPosition(pos);

	//DEBUG
	m_shape.setOutlineThickness(0.5f);
	m_shape.setOutlineColor(sf::Color::Yellow);
	m_shape.setFillColor(sf::Color::Transparent);
}

Tile::~Tile()
{

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