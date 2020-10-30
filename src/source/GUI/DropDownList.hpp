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
	DropDownList(sf::Font& mainFont,
				 const sf::Vector2f& pos, const sf::Vector2f& size, size_t chSize,
				 std::vector<std::string>& list, size_t curElem);

	~DropDownList();

	//Accessors
	size_t GetActiveElemIndex() const;

	//Modificators
	void SetPosition(const sf::Vector2f& pos);

	//Info
	std::string GetStringInfo();

	//Functions
	void Update(const sf::Vector2f& mousePos, const float& dt);
	void Render(sf::RenderTarget& target);

	void Reset(const sf::Vector2f& size_wh, const sf::Vector2f& pos, const uint32_t chSize);

private:
	Button* m_activeElem;
	std::vector<Button*> m_list;

	bool m_isOpen;
	
	//Update
	void inline UpdateList(const sf::Vector2f& mousePos, const float& dt);

	//Render
	void inline RenderList(sf::RenderTarget& target);

	//Support func
	void inline DeleteList();
};
} // !namespace GUI
#endif // !DROPDOWN_LIST_H