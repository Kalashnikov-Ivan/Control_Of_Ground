#ifndef BUTTON_H
#define BUTTON_H

namespace GUI
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

	//Accessors
		const States getState() const;
		const sf::RectangleShape getShape() const;
		const sf::Vector2f getPosition() const;
		const sf::Vector2f getSize() const;

	//Info
		std::string getStringInfo() const;

	//Functions
		void update(const sf::Vector2f& mouse_pos, const float& dt);
		void render(sf::RenderTarget& target);

		const bool isPressed() const;
private:
	//Members
	sf::RectangleShape m_shape;
	States m_state;

	sf::Text m_text;

	static float m_press_time;
	static constexpr float m_max_press_time{ 0.4f };

	//Colors
	sf::Color m_color_idle;
	sf::Color m_color_hover;
	sf::Color m_color_active;

	//Functions
	void updateTimer(const float& dt);
	const bool isTime();
};
} // !namespace cog

#endif // !BUTTON_H