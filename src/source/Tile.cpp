#include "stdHeader.hpp"

#include "Tile.hpp"

//Constructors
Tile::Tile()
	: sf::RectangleShape { sf::Vector2f(0.f, 0.f)},
	m_border_visible{ false }
{
}

Tile::Tile(const sf::Vector2f pos, const sf::Vector2f size_xy, const bool border_visible)
	: sf::RectangleShape{ size_xy },
	m_border_visible { border_visible }
{
	setPosition(pos);
	setOutlineThickness(0.51f);

	if (border_visible == true)
		setOutlineColor(sf::Color::Yellow);
	else
		setOutlineColor(sf::Color::Transparent);

	//setFillColor(sf::Color::Transparent);
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
		setOutlineColor(sf::Color::Yellow);
	else
		setOutlineColor(sf::Color::Transparent);
}

//Update
void Tile::update(const float& dt)
{
}