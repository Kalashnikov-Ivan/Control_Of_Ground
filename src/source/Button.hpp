#ifndef BUTTON_H
#define BUTTON_H

namespace cog
{
class Button
{
public:
	Button(const sf::Vector2f& pos, const sf::Vector2f& size_wh,
	sf::Font* font, const std::string& text, uint32_t ch_size,
	const sf::Color& color_idle, 
	const sf::Color& color_hover, 
	const sf::Color& color_active);
	~Button();

	//Functions
	void update(const sf::Vector2f& mouse_pos);
	void render(sf::RenderTarget* target);

	//Accessors
	const bool is_pressed() const;

	enum m_states { IS_IDLE = 0, IS_HOVER, IS_ACTIVE };

private:
	sf::RectangleShape m_shape;

	sf::Font* m_font; // -> From Child of State
	sf::Text m_text;

	//Colors
	sf::Color m_color_idle;
	sf::Color m_color_hover;
	sf::Color m_color_active;

	//States of button
	unsigned short m_state;
};
} // !namespace cog

#endif // !BUTTON_H