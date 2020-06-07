#include "PauseMenu.hpp"

using namespace GUI;

//Constructors
PauseMenu::PauseMenu(sf::RenderWindow& window, std::map<const std::string, sf::Font*>& supported_fonts)
	: Menu         { window, supported_fonts },
	m_background   { static_cast<sf::Vector2f>(window.getSize()) },
	m_container    { 
					 sf::Vector2f(static_cast<float>(window.getSize().x) / 4.f, 
						          static_cast<float>(window.getSize().y)) 
				   }
{
	initBackground();
	initButtons();
}

PauseMenu::~PauseMenu()
{

}

//Init
void PauseMenu::initBackground()
{
	m_background.setFillColor(sf::Color(20, 20, 20, 100));

	m_container.setFillColor(sf::Color(20, 20, 20, 200));
	m_container.setPosition((m_window.getSize().x / 2.f) - (m_container.getSize().x / 2.f), 0.f);
}

void PauseMenu::initButtons()
{

}

//Update
void PauseMenu::updateButtons(const sf::Vector2f& mouse_pos)
{
	Menu::updateButtons(mouse_pos);
	/*...*/
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