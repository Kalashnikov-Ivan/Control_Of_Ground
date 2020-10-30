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
		sf::Font& font, const std::string& text, uint32_t chSize,
		const sf::Color& color_idle, 
		const sf::Color& color_hover, 
		const sf::Color& color_active,
		const size_t index = 0);
	virtual ~Button();

	//Accessors
		const States GetState() const;
		const size_t GetIndex() const;
		const sf::Text GetText() const;

		const bool IsPressed() const;

	//Modificators
		void SetIndex(const size_t index);
		virtual void SetPosition(const sf::Vector2f& pos);

		void SetText(const sf::Text& text);
		void SetTextString(const std::string& str);

	//Info
		std::string SetStringInfo() const;

	//Functions
		void Update(const sf::Vector2f& mousePos, const float& dt);
		void Render(sf::RenderTarget& target);

		void Reset(const sf::Vector2f& size_wh, const sf::Vector2f& pos, const uint32_t chSize);
private:
	//Members
	States m_state;
	size_t m_index;

	sf::Text m_text;

	static float m_pressTime;
	static constexpr float m_maxPressTime{ 0.7f };

	//Colors
	sf::Color m_color_idle;
	sf::Color m_color_hover;
	sf::Color m_color_active;

	//Functions
	void UpdateTimer(const float& dt);
	const bool IsTime();
};
} // !namespace GUI
#endif // !BUTTON_H