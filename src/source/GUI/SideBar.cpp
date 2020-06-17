#include "stdHeader.hpp"

#include "SideBar.h"

using namespace GUI;

//Constructors
SideBar::SideBar(const sf::VideoMode& vm, sf::Font& main_font, const sf::Vector2f& pos,
				 const sf::Vector2f& bounds_size, const sf::Vector2f& button_size)
	: Menu { main_font },
	m_bounds { bounds_size }, m_button_size { button_size }
{
	m_bounds.setFillColor(sf::Color(192, 192, 192, 100));
	m_bounds.setOutlineThickness(0.7f);
	m_bounds.setOutlineColor(sf::Color::White);
}

SideBar::~SideBar()
{
}

//Init
void SideBar::initButtons(const sf::VideoMode& vm)
{

}


//Update
void SideBar::update(const sf::Vector2f& mouse_pos, const float& dt)
{
	updateButtons(mouse_pos, dt);
}

//Render
void SideBar::render(sf::RenderTarget& target)
{
	target.draw(m_bounds);

	renderButtons(target);
}