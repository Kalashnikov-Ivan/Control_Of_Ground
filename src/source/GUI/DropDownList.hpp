#ifndef DROPDOWN_LIST_H
#define DROPDOWN_LIST_H

#include "Button.hpp"
#include "Menu.hpp"

namespace GUI
{
class DropDownList
{
public:
	//Constructors
	DropDownList(sf::Font& main_font,
				 const sf::Vector2f& pos, const sf::Vector2f& size, size_t ch_size,
				 std::string list[], size_t quantity_elem, size_t cur_elem);

	virtual ~DropDownList();

	//Update
	void update(const sf::Vector2f& mouse_pos, const float& dt);

	//Render
	void render(sf::RenderTarget& target);

private:
	Button* m_active_element;
	std::vector<Button*> m_list;

	bool m_is_open;

	//Update
	void inline updateList(const sf::Vector2f& mouse_pos, const float& dt);

	//Render
	void inline renderList(sf::RenderTarget& target);
};
} // !namespace GUI
#endif // !DROPDOWN_LIST_H