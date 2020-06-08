#ifndef DROPDOWN_LIST_H
#define DROPDOWN_LIST_H

#include "Menu.hpp"

namespace GUI
{
class DropDownList :
	public Menu
{
public:
	//Constructors
	DropDownList(sf::RenderWindow& window,
				 std::map<const std::string, sf::Font*>& supported_fonts);

	virtual ~DropDownList();

	//Update
	virtual void update(const sf::Vector2f& mouse_pos, const float& dt) override;

	//Render
	virtual void render(sf::RenderTarget& target) override;

private:
	Button* m_active_element;

	//Init
	virtual void initButtons() override;
};
} // !namespace GUI
#endif // !DROPDOWN_LIST_H