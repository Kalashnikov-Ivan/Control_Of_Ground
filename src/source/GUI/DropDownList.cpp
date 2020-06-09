#include "stdHeader.hpp"

#include "DropDownList.hpp"

using namespace GUI;

//Constructors
DropDownList::DropDownList(sf::Font& main_font,
						   const sf::Vector2f& pos, const sf::Vector2f& size, size_t ch_size,
						   std::string list[], size_t quantity_elem, size_t cur_elem)
	: m_active_element { nullptr },
	m_is_open{ false }
{
	m_active_element = new Button{  pos, size, main_font, list[cur_elem], ch_size,
									sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200) };

	//Init list
	for (size_t i = 0; i < quantity_elem; i++)
	{
		m_list.push_back(
			new Button(
				sf::Vector2f(pos.x, pos.y + ((i+1) * size.y)), size, main_font, list[i], ch_size,
				sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200))
		);
	}
}

DropDownList::~DropDownList()
{
	delete m_active_element;

	deleteList();
}

//Support func
void DropDownList::deleteList()
{
	for (auto& i : m_list)
		delete i;
}

//Update
void DropDownList::updateList(const sf::Vector2f& mouse_pos, const float& dt)
{
	for (auto& elem : m_list)
	{
		elem->update(mouse_pos, dt);

		if (elem->isPressed())
		{
			m_is_open = false;
			m_active_element->setStringText(elem->getStringText());
		}
	}
}

void DropDownList::update(const sf::Vector2f& mouse_pos, const float& dt)
{
	m_active_element->update(mouse_pos, dt);

	if (m_is_open)
		updateList(mouse_pos, dt);

	if (m_active_element->isPressed())
	{
		if (m_is_open)
			m_is_open = false;
		else
			m_is_open = true;
	}
}

//Render
void DropDownList::renderList(sf::RenderTarget& target)
{
	for (auto& i : m_list)
		i->render(target);
}

void DropDownList::render(sf::RenderTarget& target)
{
	m_active_element->render(target);

	if (m_is_open)
		renderList(target);
}