#ifndef BUTTON_H
#define BUTTON_H

namespace GUI
{
class Button :
	public sf::RectangleShape
{
public:
	//States of button
	enum class States { NONE = -1, IDLE = 0, HOVER, ACTIVE };

	//Constructors
	Button(const sf::Vector2f& pos, const sf::Vector2f& size_wh,
		sf::Text& text,
		const sf::Color& color_idle, 
		const sf::Color& color_hover, 
		const sf::Color& color_active,
		const size_t index = 0);

	Button(const sf::Vector2f& pos, const sf::Vector2f& size_wh,
		sf::Font& font, const std::string& text, uint32_t ch_size,
		const sf::Color& color_idle, 
		const sf::Color& color_hover, 
		const sf::Color& color_active,
		const size_t index = 0);
	virtual ~Button();

	//Accessors
		const States getState() const;
		const size_t getIndex() const;
		const sf::Text getText() const;

		const bool isPressed() const;

	//Modificators
		void setIndex(const size_t index);
		virtual void setPosition(const sf::Vector2f& pos);

		void setText(const sf::Text& text);
		void setTextString(const std::string& str);

	//Info
		std::string getStringInfo() const;

	//Functions
		void update(const sf::Vector2f& mouse_pos, const float& dt);
		void render(sf::RenderTarget& target);

		void reset(const sf::Vector2f& size_wh, const sf::Vector2f& pos, const uint32_t ch_size);
private:
	//Members
	States m_state;
	size_t m_index;

	sf::Text m_text;

	static float m_press_time;
	static constexpr float m_max_press_time{ 0.7f };

	//Colors
	sf::Color m_color_idle;
	sf::Color m_color_hover;
	sf::Color m_color_active;

	//Functions
	void updateTimer(const float& dt);
	const bool isTime();
};
} // !namespace GUI

#endif // !BUTTON_H