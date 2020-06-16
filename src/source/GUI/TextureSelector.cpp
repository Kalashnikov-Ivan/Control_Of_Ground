#include "stdHeader.hpp"

#include "TextureSelector.h"

using namespace GUI;

//Constructors
TextureSelector::TextureSelector(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Texture* texture_sheet, sf::Vector2f& grid_size)
	: m_bounds { size },
	m_sheet    { *texture_sheet },
	m_grid_size{ grid_size }, m_selector { grid_size }, m_selected_rect { 0, 0, static_cast<int>(m_grid_size.x), static_cast<int>(m_grid_size.y) },
	m_active   { false }, m_hidden { false }
{
	m_bounds.setPosition(pos);
	m_bounds.setFillColor(sf::Color(50, 50, 50, 100));
	m_bounds.setOutlineThickness(1.f);
	m_bounds.setOutlineColor(sf::Color::Red);

	m_sheet.setPosition(pos);
	
	if (m_sheet.getGlobalBounds().width > m_bounds.getGlobalBounds().width)
	{
		m_sheet.setTextureRect(sf::IntRect(0, 0, int(m_bounds.getGlobalBounds().width), int(m_sheet.getGlobalBounds().height)));
	}

	if (m_sheet.getGlobalBounds().height > m_bounds.getGlobalBounds().height)
	{
		m_sheet.setTextureRect(sf::IntRect(0, 0, int(m_sheet.getGlobalBounds().height), int(m_bounds.getGlobalBounds().width)));
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
std::string TextureSelector::getStringInfo()
{
	std::stringstream result;

	result << "Selector::grid pos: " << m_mouse_pos_grid.x << ' ' << m_mouse_pos_grid.y << '\n';

	return result.str();
}

bool TextureSelector::isActive() const
{
	return m_active;
}

//Accessors
sf::Vector2f TextureSelector::getGridSize() const
{
	return m_grid_size;
}

const sf::IntRect& TextureSelector::getSelectedRect() const
{
	return m_selected_rect;
}

//Functions
bool TextureSelector::isContain(const sf::Vector2f& mouse_pos) const
{
	if (m_bounds.getGlobalBounds().contains(mouse_pos))
		return true;
	else
		return false;
}

//Update
void inline TextureSelector::updateSelectorRect()
{
	m_selected_rect.left = static_cast<int>(m_selector.getPosition().x - m_bounds.getPosition().x);
	m_selected_rect.top = static_cast<int>(m_selector.getPosition().y - m_bounds.getPosition().y);
}

void TextureSelector::update(const sf::Vector2f& mouse_pos, const float& dt)
{
	if (!m_hidden)
	{
		if (m_bounds.getGlobalBounds().contains(mouse_pos))
			m_active = true;
		else
			m_active = false;

		if (m_active)
		{
			m_mouse_pos_grid.x = static_cast<unsigned>((mouse_pos.x - m_bounds.getPosition().x) / (m_grid_size.x));
			m_mouse_pos_grid.y = static_cast<unsigned>((mouse_pos.y - m_bounds.getPosition().y) / (m_grid_size.y));

			m_selector.setPosition(
				m_bounds.getPosition().x + m_mouse_pos_grid.x * m_grid_size.x,
				m_bounds.getPosition().y + m_mouse_pos_grid.y * m_grid_size.y
			);

			updateSelectorRect();
		}
	}
}

//Render
void TextureSelector::render(sf::RenderTarget& target)
{
	if (!m_hidden)
	{
		target.draw(m_bounds);
		target.draw(m_sheet);

		if (m_active)
			target.draw(m_selector);
	}
}
