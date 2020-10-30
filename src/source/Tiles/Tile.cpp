#include "stdafx.h"

#include "Tile.hpp"

using namespace Tiles;

//Constructors
Tile::Tile()
	: sf::RectangleShape{ sf::Vector2f(0.f, 0.f) }
	, m_borderVisible   { false }
{
}

Tile::Tile(const sf::Vector2f pos, const sf::Vector2f size_xy, const sf::Texture* texture, const sf::IntRect textureRect,
		  const bool border_visible)
	: sf::RectangleShape{ size_xy }
	, m_borderVisible   { border_visible }
{
	setPosition(pos);
	setOutlineThickness(0.51f);

	if (border_visible == true)
		setOutlineColor(sf::Color::Yellow);
	else
		setOutlineColor(sf::Color::Transparent);

	//setFillColor(sf::Color::Transparent);
	setTexture(texture);
	setTextureRect(textureRect);
}

Tile::~Tile()
{

}

//Accessors
bool Tile::GetBorberVisible() const
{
	return m_borderVisible;
}

//Modificators
void Tile::SetBorderVisible(const bool option)
{
	m_borderVisible = option;

	if (option == true)
		setOutlineColor(sf::Color::Yellow);
	else
		setOutlineColor(sf::Color::Transparent);
}

//Update
void Tile::Update(const float& dt)
{
}