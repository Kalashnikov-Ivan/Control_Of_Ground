#ifndef TEXTURE_SELECTOR_H
#define TEXTURE_SELECTOR_H

namespace GUI
{
class TextureSelector :
	public sf::RectangleShape
{
public:
	//Constructors
	TextureSelector(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Texture* texture_sheet, sf::Vector2f& grid_size);
	~TextureSelector();

	//Info
	std::string getStringInfo();

	//Accessors
	bool isActive() const;
	bool isHidden() const;
	sf::Vector2f getGridSize() const;
	const sf::IntRect& getSelectedRect() const;

	//Modificators
	virtual void setPosition(const float x, const float y);
	virtual void setPosition(const sf::Vector2f& pos);

	void setHidden(const bool option);

	//Functions
	void update(const sf::Vector2f& mouse_pos, const float& dt);
	void render(sf::RenderTarget& target);

	void reset(const sf::Vector2f& size, const sf::Vector2f& pos);

private:
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