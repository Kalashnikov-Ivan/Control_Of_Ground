#ifndef BUTTON_H
#define BUTTON_H

namespace Core
{
class Button
{
public:
	//States of button
	enum class States { NONE = -1, IDLE = 0, HOVER, ACTIVE };

	//Constructors
	Button(const sf::Vector2f& pos, const sf::Vector2f& size_wh,
			sf::Font& font, const std::string& text, uint32_t ch_size,
			const sf::Color& color_idle, 
			const sf::Color& color_hover, 
			const sf::Color& color_active);
	~Button();

	//Functions
	void update(const sf::Vector2f& mouse_pos);
	void render(sf::RenderTarget& target);

	//Accessors
	const States getState() const;
	const sf::RectangleShape getShape() const;
	const sf::Vector2f getPosition() const;
	const sf::Vector2f getSize() const;
	const bool isPressed() const;

	//Info
	std::string getStringInfo() const;

private:
	//Members
	sf::RectangleShape m_shape;
	States m_state;

	sf::Text m_text;

	//Colors
	sf::Color m_color_idle;
	sf::Color m_color_hover;
	sf::Color m_color_active;
};
} // !namespace cog

#endif // !BUTTON_H