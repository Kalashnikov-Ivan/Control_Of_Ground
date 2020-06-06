#include "PauseMenu.hpp"

using namespace GUI;

//Constructors
PauseMenu::PauseMenu(sf::RenderWindow& window)
	: Menu{ static_cast<sf::Vector2f>(window.getSize()) },
	m_container    { 
					 sf::Vector2f(static_cast<float>(window.getSize().x) / 4.f, 
						          static_cast<float>(window.getSize().y)) 
				   }
{
	m_background.setFillColor(sf::Color(192, 192, 192, 100));

	m_container.setFillColor(sf::Color(192, 192, 192, 200));
	m_container.setPosition((window.getSize().x / 2.f) - (m_container.getSize().x / 2.f), 0.f);
}

PauseMenu::~PauseMenu()
{

}

//Init
void PauseMenu::initBackground()
{
}

void PauseMenu::initButtons()
{

}

//Update
void PauseMenu::updateButtons(const sf::Vector2f& mouse_pos)
{
	for (auto& i : m_buttons)
		i.second->update(mouse_pos);
}

void PauseMenu::update(const sf::Vector2f& mouse_pos_window)
{
	updateButtons(mouse_pos_window);
}

//Render
void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(m_background);
	target.draw(m_container);

	renderButtons(target);
}