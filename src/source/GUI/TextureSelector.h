#ifndef TEXTURE_SELECTOR_H
#define TEXTURE_SELECTOR_H

namespace GUI
{
class TextureSelector
{
public:
	//Constructors
	TextureSelector(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Texture* texture_sheet, sf::Vector2f& grid_size);
	~TextureSelector();

	//Info
	std::string getStringInfo();

	//Accessors
	bool isActive() const;
	sf::Vector2f getGridSize() const;
	const sf::IntRect& getSelectedRect() const;

	//Functions
	bool isContain(const sf::Vector2f& mouse_pos) const;

	//Update
	void update(const sf::Vector2f& mouse_pos, const float& dt);

	//Render
	void render(sf::RenderTarget& target);

private:
	bool m_active;
	sf::RectangleShape m_bounds;
	sf::Sprite m_sheet;

	sf::Vector2f m_grid_size;
	sf::RectangleShape m_selector;
	sf::Vector2u m_mouse_pos_grid;

	sf::IntRect m_selected_rect;

	//Functions
	void inline updateSelectorRect();
};
} // !namespace GUI
#endif // !TEXTURE_SELECTOR_H