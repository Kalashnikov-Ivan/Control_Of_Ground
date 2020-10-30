#ifndef TEXTURE_SELECTOR_H
#define TEXTURE_SELECTOR_H

namespace GUI
{
class TextureSelector :
	public sf::RectangleShape
{
public:
//Constructors
	TextureSelector(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Texture* textureSheet, sf::Vector2f& gridSize);
	~TextureSelector();

//Info
	std::string GetStringInfo();

//Accessors
	bool IsActive() const;
	bool IsHidden() const;
	sf::Vector2f GetGridSize() const;
	const sf::IntRect& GetSelectedRect() const;

//Modificators
	virtual void setPosition(const float x, const float y);
	virtual void setPosition(const sf::Vector2f& pos);

	void SetHidden(const bool option);

//Functions
	void Update(const sf::Vector2f& mousePos, const float& dt);
	void Render(sf::RenderTarget& target);

	void Reset(const sf::Vector2f& size, const sf::Vector2f& pos);

private:
	sf::Sprite m_sheet;

	sf::RectangleShape m_selector;
	sf::Vector2f m_gridSize;
	sf::Vector2u m_mousePosGrid;

	sf::IntRect m_selectedRect;

	bool m_hidden;
	bool m_active;

	//Functions
	void inline UpdateSelectorRect();
};
} // !namespace GUI
#endif // !TEXTURE_SELECTOR_H