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

	void update(const sf::Vector2f& mouse_pos, const float& dt);
	void render(sf::RenderTarget& target);

	void reset(const sf::Vector2f& size, const sf::Vector2f& pos);

private:
	sf::RectangleShape m_bounds;
	sf::Sprite m_sheet;

	sf::RectangleShape m_selector;
	sf::Vector2f m_grid_size;
	sf::Vector2u m_mouse_pos_grid;

	sf::IntRect m_selected_rect;

	bool m_hidden;
	bool m_active;

	//Functions
	void inline updateSelectorRect();
};
} // !namespace GUI
#endif // !TEXTURE_SELECTOR_H