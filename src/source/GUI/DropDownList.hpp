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
				 std::vector<std::string>& list, size_t cur_elem);

	virtual ~DropDownList();

	//Accessors
	size_t getActiveElemIndex() const;

	//Modificators
	void setPosition(const sf::Vector2f& pos);

	//Info
	std::string getStringInfo();

	//Functions
	void update(const sf::Vector2f& mouse_pos, const float& dt);
	void render(sf::RenderTarget& target);

	void reset(const sf::Vector2f& size_wh, const sf::Vector2f& pos, const uint32_t ch_size);

private:
	Button* m_active_element;
	std::vector<Button*> m_list;

	bool m_is_open;
	
	//Update
	void inline updateList(const sf::Vector2f& mouse_pos, const float& dt);

	//Render
	void inline renderList(sf::RenderTarget& target);

	//Support func
	void inline deleteList();
};
} // !namespace GUI
#endif // !DROPDOWN_LIST_H