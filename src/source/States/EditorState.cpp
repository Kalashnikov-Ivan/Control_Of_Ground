#include "stdHeader.hpp"

#include "EditorState.hpp"

#include "States/SettingsState.hpp"

#define DEBUG

using namespace States;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////

EditorState::EditorState(StateData& Sdata, const float click_time)
	: State{ Sdata },
	m_tile_map { nullptr }, m_texture_selector{ nullptr },
	m_pause_menu { m_Sdata.window, *m_Sdata.supported_fonts["DOSIS"], m_Sdata.supported_fonts},
	m_selector   { m_Sdata.grid_size_f },
	m_click_time { click_time }
{
	initTextures();
	initKeybinds();

	m_selector.setOutlineThickness(1.5f);
	m_selector.setOutlineColor(sf::Color::Green);
	m_selector.setFillColor(sf::Color::Transparent);

	m_tile_map = new TileMap(Sdata.grid_size_f, sf::Vector2u(50, 50));

	sf::Vector2f grid_size = sf::Vector2f(32.f, 32.f);
	m_texture_selector = new GUI::TextureSelector(sf::Vector2f(320.f, 192.f), sf::Vector2f(1000.f, 0.f), m_textures["TILE_SHEET"], grid_size);
}

EditorState::~EditorState()
{
	delete m_texture_selector;
	delete m_tile_map;
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void EditorState::initTextures()
{
	m_textures["TILE_0"] = new sf::Texture();

	if (!m_textures["TILE_0"]->loadFromFile("resources/textures/Tile_02.png"))
		throw "ERROR::EditorState::inittTextures::TILE_0 - failed to load texture resources/textures/Tile_02.png";

	m_textures["TILE_SHEET"] = new sf::Texture();

	if (!m_textures["TILE_SHEET"]->loadFromFile("resources/textures/Tileset.png"))
		throw "ERROR::EditorState::inittTextures::TILE_SHEET - failed to load texture resources/textures/Tileset.png";
}

void EditorState::initKeybinds()
{
#ifdef DEBUG
	std::cout << "EditorState: Start of init_keybinds..." << std::endl;
#endif // DEBUG

	std::ifstream keys_ifs("config/EditorState_keybinds.ini");
	if (keys_ifs.is_open())
	{
		std::string key{ "" };
		std::string key_value{ "" };

		while (keys_ifs >> key >> key_value)
		{
			m_keybinds[key] = m_Sdata.supported_keys.at(key_value);
		}
	}
	else
	{
		std::cerr << "config/EditorState.ini - cannot open!"
			<< std::endl
			<< "Using default keys..." << std::endl;

		m_keybinds["CLOSE"] = m_Sdata.supported_keys.at("Escape");
	}

	keys_ifs.close();

#ifdef DEBUG
	for (auto& i : m_keybinds)
		std::cout << i.first << " = " << i.second << std::endl;

	std::cout << "EditorState: init_keybinds is success!" << std::endl;
#endif // DEBUG
}


////////////////////////////////////////////////////////////
// Tech info
////////////////////////////////////////////////////////////
std::string EditorState::getStringInfo()
{
	std::stringstream result;

	result << getStringMousePos();

	if (m_texture_selector->isActive())
	{
		result << m_texture_selector->getStringInfo();
	}
	else
	{
		result << "Grid pos: " << m_mouse_pos_grid.x << ' ' << m_mouse_pos_grid.y << '\n';
	}

	result << m_pause_menu.getStringInfo();

	return result.str();
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void EditorState::updateEvent(const sf::Event& event)
{
	if (event.type == sf::Event::LostFocus)
	{
		if (!m_paused)
			pause();
	}

	if (event.type == sf::Event::KeyPressed)
	{

		if (event.key.code == (sf::Keyboard::Key(m_keybinds["CLOSE"])))
		{
			if (!m_paused)
				pause();
			else
				unpause();
		}

		if (event.key.code == (sf::Keyboard::Key(m_keybinds["SWITCH_TILE_BORDER_VISIBLE"])))
		{
			if (!m_tile_map->getTilesBorderVisible())
				m_tile_map->setTilesBorderVisible(true);
			else
				m_tile_map->setTilesBorderVisible(false);
		}
	}
}

void EditorState::updateInput(const float& dt)
{
	m_selector.setPosition(m_mouse_pos_grid.x * m_Sdata.grid_size_f.x, m_mouse_pos_grid.y * m_Sdata.grid_size_f.y);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isTime())
	{
		if (m_texture_selector->isActive())
		{
			m_selected_rect = m_texture_selector->getSelectedRect();
		}
		else
		{
			m_tile_map->addTile(m_mouse_pos_grid.x, m_mouse_pos_grid.y, 0, m_textures["TILE_SHEET"], m_selected_rect);
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && isTime())
	{
		if (m_texture_selector->isActive())
		{

		}
		else
		{
			m_tile_map->deleteTile(m_mouse_pos_grid.x, m_mouse_pos_grid.y, 0);
		}
	}
}

void EditorState::updatePauseInput(const float& dt)
{
	if (m_pause_menu.isButtonPressed("SETTINGS_STATE"))
		m_Sdata.states.push(new SettingsState{ m_Sdata });

	if (m_pause_menu.isButtonPressed("EXIT"))
		quitState();
}

//Timer
void EditorState::updateTimer(const float& dt)
{
	m_timer += dt;
}

bool EditorState::isTime()
{
	if (m_timer >= m_click_time)
	{
		m_timer = 0.f;
		return true;
	}

	return false;
}

void EditorState::update(const float& dt)
{
	updateTimer(dt);
	updateMousePos();

	if (!m_paused)
	{
		updateInput(dt);

		m_texture_selector->update(m_mouse_pos_view, dt);
	}
	else
	{
		updatePauseInput(dt);

		m_pause_menu.update(m_mouse_pos_view, dt);
	}
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void EditorState::render(sf::RenderTarget& target)
{
	m_tile_map->render(target);
	m_texture_selector->render(target);

	if (!m_texture_selector->isActive())
		target.draw(m_selector);

	if (m_paused)
	{
		m_pause_menu.render(target);
	}
}