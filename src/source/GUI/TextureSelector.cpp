#include "stdafx.h"

#include "TextureSelector.h"

using namespace GUI;

//Constructors
TextureSelector::TextureSelector(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Texture* textureSheet, sf::Vector2f& gridSize)
	: sf::RectangleShape { size }
	, m_sheet            { *textureSheet }
	, m_gridSize         { gridSize }
	, m_selector         { gridSize }
	, m_selectedRect     { 0, 0, static_cast<int>(m_gridSize.x), static_cast<int>(m_gridSize.y) }
	, m_active           { false }
	, m_hidden           { false }
{
	setPosition(pos);
	setFillColor(sf::Color(50, 50, 50, 100));
	setOutlineThickness(1.f);
	setOutlineColor(sf::Color::Red);

	m_sheet.setPosition(pos);
	
	if (m_sheet.getGlobalBounds().width >getGlobalBounds().width)
	{
		m_sheet.setTextureRect(sf::IntRect(0, 0, int(getGlobalBounds().width), int(m_sheet.getGlobalBounds().height)));
	}

	if (m_sheet.getGlobalBounds().height > getGlobalBounds().height)
	{
		m_sheet.setTextureRect(sf::IntRect(0, 0, int(m_sheet.getGlobalBounds().height), int(getGlobalBounds().width)));
	}

	m_selector.setPosition(pos);
	m_selector.setOutlineThickness(0.6f);
	m_selector.setOutlineColor(sf::Color::Green);
	m_selector.setFillColor(sf::Color::Transparent);
}

TextureSelector::~TextureSelector()
{

}

//Info
std::string TextureSelector::GetStringInfo()
{
	std::stringstream result;

	result << "Selector::grid pos: " << m_mousePosGrid.x << ' ' << m_mousePosGrid.y << '\n';

	return result.str();
}

bool TextureSelector::IsActive() const
{
	return m_active;
}

bool TextureSelector::IsHidden() const
{
	return m_hidden;
}

//Accessors
sf::Vector2f TextureSelector::GetGridSize() const
{
	return m_gridSize;
}

const sf::IntRect& TextureSelector::GetSelectedRect() const
{
	return m_selectedRect;
}

//Functions
void inline TextureSelector::UpdateSelectorRect()
{
	m_selectedRect.left = static_cast<int>(m_selector.getPosition().x - getPosition().x);
	m_selectedRect.top  = static_cast<int>(m_selector.getPosition().y - getPosition().y);
}

//Modificators
void TextureSelector::setPosition(const float x, const float y)
{
	sf::RectangleShape::setPosition(x, y);

	m_sheet.setPosition(x, y);
}

void TextureSelector::setPosition(const sf::Vector2f& pos)
{
	sf::RectangleShape::setPosition(pos);

	m_sheet.setPosition(pos);
}

void TextureSelector::SetHidden(const bool option)
{
	m_hidden = option;
}

void TextureSelector::Update(const sf::Vector2f& mousePos, const float& dt)
{
	if (!m_hidden)
	{
		if (getGlobalBounds().contains(mousePos))
			m_active = true;
		else
			m_active = false;

		if (m_active)
		{
			m_mousePosGrid.x = static_cast<unsigned>((mousePos.x - getPosition().x) / (m_gridSize.x));
			m_mousePosGrid.y = static_cast<unsigned>((mousePos.y - getPosition().y) / (m_gridSize.y));

			m_selector.setPosition(
				getPosition().x + m_mousePosGrid.x * m_gridSize.x,
				getPosition().y + m_mousePosGrid.y * m_gridSize.y
			);

			UpdateSelectorRect();
		}
	}
}

//Render
void TextureSelector::Render(sf::RenderTarget& target)
{
	if (!m_hidden)
	{
		target.draw(*this);
		target.draw(m_sheet);

		if (m_active)
			target.draw(m_selector);
	}
}

void TextureSelector::Reset(const sf::Vector2f& size, const sf::Vector2f& pos)
{
	setSize(size);
	setPosition(pos);
	
	m_sheet.setPosition(pos);

	if (m_sheet.getGlobalBounds().width > getGlobalBounds().width)
	{
		m_sheet.setTextureRect(sf::IntRect(0, 0, int(getGlobalBounds().width), int(m_sheet.getGlobalBounds().height)));
	}

	if (m_sheet.getGlobalBounds().height > getGlobalBounds().height)
	{
		m_sheet.setTextureRect(sf::IntRect(0, 0, int(m_sheet.getGlobalBounds().height), int(getGlobalBounds().width)));
	}
}