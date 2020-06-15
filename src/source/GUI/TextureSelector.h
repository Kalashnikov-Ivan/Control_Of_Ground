#ifndef TEXTURE_SELECTOR_H
#define TEXTURE_SELECTOR_H

namespace GUI
{
class TextureSelector
{
public:
	//Constructors
	TextureSelector(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Texture* texture_sheet, size_t grid_size);
	~TextureSelector();

	//Info
	std::string getStringInfo();

	//Update
	void update(const sf::Vector2f& mouse_pos, const float& dt);

	//Render
	void render(sf::RenderTarget& target);

private:
	bool m_visible;
	sf::RectangleShape m_bounds;
	sf::Sprite m_sheet;

	sf::RectangleShape m_selector;
	size_t m_grid_size;
	sf::Vector2u m_mouse_pos_grid;
};
} // !namespace GUI
#endif // !TEXTURE_SELECTOR_H