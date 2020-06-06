#include "Menu.hpp"

using namespace GUI;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Menu::Menu(sf::Vector2f background_size)
	: m_background{ background_size }
{

}
Menu::~Menu()
{
	deleteButtons();
}

//Support_cleaner
void Menu::deleteButtons()
{
	for (auto& i : m_buttons)
		delete i.second;
}

////////////////////////////////////////////////////////////
// Info
////////////////////////////////////////////////////////////
std::string Menu::getStringInfo()
{
	std::stringstream result;

	for (auto& i : m_buttons)
		if (i.second->getState() == Button::States::HOVER)
			result << i.second->getStringInfo();

	return result.str();
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void Menu::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : m_buttons)
		i.second->render(target);
}
