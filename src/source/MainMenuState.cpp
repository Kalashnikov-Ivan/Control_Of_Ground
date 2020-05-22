#include "stdHeader.hpp"

#include "MainMenuState.hpp"

#define DEBUG

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MainMenuState::MainMenuState(sf::RenderWindow* window, 
	std::map<const std::string, int>* supported_keys, std::stack<State*>* states) 
	: State{ window, supported_keys, states }
{
	init_textures();
	init_background();
	init_fonts();
	init_buttons();
}

MainMenuState::~MainMenuState()
{
	delete_buttons();
}

//Support_cleaner
void MainMenuState::delete_buttons()
{
	for (auto& i : m_buttons)
		delete i.second;
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void MainMenuState::init_textures()
{
	m_textures["BACKGROUND"] = new sf::Texture();

	if (!m_textures["BACKGROUND"]->loadFromFile("resources/textures/MainMenu/Background.jpg"))
		throw "ERROR::MainMenuState::init_background - failed to load texture";
}
void MainMenuState::init_background()
{
	m_background.setSize(static_cast<sf::Vector2f>(m_window->getSize()));

	m_background.setTexture(m_textures["BACKGROUND"]);
}

void MainMenuState::init_fonts()
{
	if (!m_font.loadFromFile("resources/fonts/Dosis-Regular.ttf"))
		throw "ERROR::MainMenuState: init_fonts. Can't open font";
}

void MainMenuState::init_buttons()
{
	unsigned int font_size = 26U;

	float button_width = 230.f;
	float button_height = 85.f;

	float default_position_x = (m_window->getSize().x / 2.f) - (button_width / 2.f); // 150.f;
	float default_position_y = (m_window->getSize().y / 2.f) - (button_height / 2.f); // 350.f;
	float default_ofset = 120.f;

	m_buttons["GAME_STATE"] = new Button{ sf::Vector2f(default_position_x, default_position_y), 
								sf::Vector2f(button_width, button_height),
								&m_font, "New Game", font_size,
								sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20,20,20,200) };

	m_buttons["SETTINGS"] = new Button{ sf::Vector2f(default_position_x, default_position_y + default_ofset),
								sf::Vector2f(button_width, button_height),
								&m_font, "Settings", font_size,
								sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20,20,20,200) };

	m_buttons["EXIT_STATE"] = new Button{ sf::Vector2f(default_position_x, default_position_y + default_ofset * 2),
								sf::Vector2f(button_width, button_height),
								&m_font, "Exit", font_size,
								sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20,20,20,200) };

}

void MainMenuState::init_keybinds()
{
}

////////////////////////////////////////////////////////////
// Virtual override
////////////////////////////////////////////////////////////
void MainMenuState::update_input(const float& dt)
{
}

void MainMenuState::update_buttons(const float& dt)
{
	for (auto& i : m_buttons)
		i.second->update(m_mouse_pos_view);

	if (m_buttons["GAME_STATE"]->is_pressed())
		m_states->push(new GameState{ m_window, m_supported_keys, m_states });
	
	if (m_buttons["EXIT_STATE"]->is_pressed())
		end_state();
}

void MainMenuState::render_buttons(sf::RenderTarget* target)
{
	for (auto& i : m_buttons)
		i.second->render(target);
}

void MainMenuState::update(const float& dt)
{
	update_mouse_pos();

	update_input(dt);
	update_buttons(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	target->draw(m_background);
	render_buttons(target);
	target->draw(get_mouse_pos_text(m_font));
}