#include "stdHeader.hpp"

#include "TextureSelector.h"

using namespace GUI;

//Constructors
TextureSelector::TextureSelector(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Texture* texture_sheet, size_t grid_size)
	: m_bounds { size },
	m_sheet    { *texture_sheet },
	m_grid_size{ grid_size },
	m_visible  { true }
{
	m_bounds.setPosition(pos);
	m_bounds.setFillColor(sf::Color(50, 50, 50, 100));
	m_bounds.setOutlineThickness(1.f);
	m_bounds.setOutlineColor(sf::Color::Red);

	m_sheet.setPosition(pos);
	//m_sheet.setScale(sf::Vector2f(2.f, 2.f));

	
	if (m_sheet.getGlobalBounds().width > m_bounds.getGlobalBounds().width)
	{
		m_sheet.setTextureRect(sf::IntRect(0, 0, m_bounds.getGlobalBounds().width, m_sheet.getGlobalBounds().height));
	}

	if (m_sheet.getGlobalBounds().height > m_bounds.getGlobalBounds().height)
	{
		m_sheet.setTextureRect(sf::IntRect(0, 0, m_sheet.getGlobalBounds().height, m_bounds.getGlobalBounds().width));
	}
	
}

TextureSelector::~TextureSelector()
{

}

//Info
std::string TextureSelector::getStringInfo()
{
	return std::string();
}

//Update
void TextureSelector::update(const sf::Vector2f& mouse_pos, const float& dt)
{
}

//Render
void TextureSelector::render(sf::RenderTarget& target)
{
	target.draw(m_bounds);
	target.draw(m_sheet);
}
