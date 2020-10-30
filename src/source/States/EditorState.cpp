#include "stdafx.h"

#include "GUI/Converter.h"

#include "EditorState.hpp"

#include "States/SettingsState.hpp"

#define DEBUG

using namespace States;

// Constructors
EditorState::EditorState(StateContext& ctx, const float clickTime)
	: State             { ctx }
	, m_tileMap         { nullptr }
	, m_textureSelector { nullptr }
	, m_pauseMenu       { ctx.settings.m_graphics->m_resolution, *m_stateContext.supportedFonts["DOSIS"], m_stateContext.supportedFonts}
	, m_selector        { m_stateContext.gridSze }
	, m_sidebar    { 
					sf::Vector2f(
						GUI::Converter::Сalc(96.f, ctx.settings.m_graphics->m_resolution.width),
						0.f
					),
					sf::Vector2f(
						GUI::Converter::Сalc(4.f, ctx.settings.m_graphics->m_resolution.width),
						GUI::Converter::Сalc(28.f, ctx.settings.m_graphics->m_resolution.height)
					),
					GUI::Converter::Сalc(
						25.f, 
						GUI::Converter::Сalc(30.f, ctx.settings.m_graphics->m_resolution.height)
					)
				 }
	, m_clickTime { clickTime }
{
	InitTextures();
	InitKeybinds();

	m_selector.setOutlineThickness(1.5f);
	m_selector.setOutlineColor(sf::Color::Green);
	m_selector.setFillColor(sf::Color::Transparent);

	m_tileMap = std::make_unique<Tiles::TileMap>(ctx.gridSze, sf::Vector2u(50, 50), m_textures["TILE_SHEET"]);


	m_sidebar.AddButton(
		"TS_0", *m_stateContext.supportedFonts["DOSIS"], "TS_0",
		sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200)
	);

	sf::Vector2f gridSize = sf::Vector2f(32.f, 32.f);
	m_textureSelector = std::make_unique<GUI::TextureSelector>(
		sf::Vector2f(320.f, 192.f), sf::Vector2f(m_stateContext.window.getSize().x - 400.f, 0.f),
		m_textures["TILE_SHEET"].get(), gridSize
	);

	//m_textureSelector->setOrigin(sf::Vector2f(320.f, 0));
	m_textureSelector->setPosition(m_sidebar.GetButton("TS_0").getPosition().x - 320.f, 0);
}

EditorState::~EditorState()
{
}

// Init
void EditorState::InitTextures()
{
	const std::string root = "resources/textures/";

	m_textures["TILE_SHEET"] = std::make_shared<sf::Texture>();

	if (!m_textures["TILE_SHEET"]->loadFromFile(root + "Tileset.png"))
		throw std::runtime_error("EditorState::initTextures::TILE_SHEET - loading texture" + root + "Tileset.png" + " failed...");
}

void EditorState::InitKeybinds()
{
#ifdef DEBUG
	std::cout << "EditorState: Start of init_keybinds..." << std::endl;
#endif // DEBUG

	std::ifstream keysIfs("config/EditorState_keybinds.ini");
	if (keysIfs.is_open())
	{
		std::string key{ "" };
		std::string val{ "" };

		while (keysIfs >> key >> val)
		{
			m_keybinds[key] = m_stateContext.supportedKeys.at(val);
		}
	}
	else
	{
		std::cerr << "config/EditorState.ini - cannot open!"
				  << std::endl
				  << "Using default keys..." << std::endl;

		m_keybinds["CLOSE"] = m_stateContext.supportedKeys.at("Escape");
	}

#ifdef DEBUG
	for (auto& i : m_keybinds)
		std::cout << i.first << " = " << i.second << std::endl;

	std::cout << "EditorState: init_keybinds is success!" << std::endl;
#endif // DEBUG
}

// Tech info
std::string EditorState::GetStringInfo()
{
	std::stringstream result;

	result << GetStringMousePos();

	if (m_textureSelector->IsActive())
	{
		result << m_textureSelector->GetStringInfo();
	}
	else
	{
		result << "Grid pos: " << m_mousePosGrid.x << ' ' << m_mousePosGrid.y << '\n';
	}

	result << m_pauseMenu.GetStringInfo();

	return result.str();
}

// Update
void EditorState::UpdateEvent(const sf::Event& event)
{
	if (event.type == sf::Event::LostFocus)
	{
		if (!m_paused)
			Pause();
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == (sf::Keyboard::Key(m_keybinds["CLOSE"])))
		{
			if (!m_paused)
				Pause();
			else
				Unpause();
		}

		if (event.key.code == (sf::Keyboard::Key(m_keybinds["SWITCH_TILE_BORDER_VISIBLE"])))
		{
			if (!m_tileMap->GetTilesBorderVisible())
				m_tileMap->SetTilesBorderVisible(true);
			else
				m_tileMap->SetTilesBorderVisible(false);
		}
	}
}

void EditorState::UpdateInput(const float& dt)
{
	m_selector.setPosition(m_mousePosGrid.x * m_stateContext.gridSze.x, m_mousePosGrid.y * m_stateContext.gridSze.y);

	if (m_sidebar.IsButtonPressed("TS_0"))
	{
		if (!m_textureSelector->IsHidden())
			m_textureSelector->SetHidden(true);
		else
			m_textureSelector->SetHidden(false);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && IsTime() && !m_sidebar.getGlobalBounds().contains(m_mousePosView))
	{
		if (m_textureSelector->IsActive())
		{
			m_selectedRect = m_textureSelector->GetSelectedRect();
		}
		else
		{
			m_tileMap->AddTile(m_mousePosGrid.x, m_mousePosGrid.y, 0, m_textures["TILE_SHEET"].get(), m_selectedRect);
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && IsTime())
	{
		if (m_textureSelector->IsActive())
		{

		}
		else
		{
			m_tileMap->DeleteTile(m_mousePosGrid.x, m_mousePosGrid.y, 0);
		}
	}
}

void EditorState::UpdatePauseInput(const float& dt)
{
	if (m_pauseMenu.IsButtonPressed("SETTINGS_STATE"))
		m_stateContext.states.push_back(std::make_unique<SettingsState>(m_stateContext));

	if (m_pauseMenu.IsButtonPressed("EXIT"))
		QuitState();
}

//Timer
void EditorState::UpdateTimer(const float& dt)
{
	m_timer += dt;
}

bool EditorState::IsTime()
{
	if (m_timer >= m_clickTime)
	{
		m_timer = 0.f;
		return true;
	}

	return false;
}

void EditorState::Update(const float& dt)
{
	UpdateTimer(dt);
	UpdateMousePos();

	if (!m_paused)
	{
		UpdateInput(dt);

		m_sidebar.Update(m_mousePosView, dt);
		m_textureSelector->Update(m_mousePosView, dt);
	}
	else
	{
		UpdatePauseInput(dt);

		m_pauseMenu.Update(m_mousePosView, dt);
	}
}

// Render
void EditorState::Render(sf::RenderTarget& target)
{
	m_tileMap->Render(target);
	m_sidebar.Render(target);
	m_textureSelector->Render(target);

	if (!m_textureSelector->IsActive() && !m_sidebar.getGlobalBounds().contains(m_mousePosView))
	{
		target.draw(m_selector);
	}

	if (m_paused)
	{
		m_pauseMenu.Render(target);
	}
}

//Reset
void EditorState::Reset(const sf::VideoMode& vm)
{
	m_sidebar.Reset(
		sf::Vector2f(
			GUI::Converter::Сalc(96.f, m_stateContext.settings.m_graphics->m_resolution.width),
			0.f
		),
		sf::Vector2f(
			GUI::Converter::Сalc(4.f, m_stateContext.settings.m_graphics->m_resolution.width),
			GUI::Converter::Сalc(28.f, m_stateContext.settings.m_graphics->m_resolution.height)
		),
		GUI::Converter::Сalc(25.f, GUI::Converter::Сalc(30.f, m_stateContext.settings.m_graphics->m_resolution.height))
	);

	m_pauseMenu.Reset(vm);

	//TextureSelector
	m_textureSelector->setPosition(m_sidebar.GetButton("TS_0").getPosition().x - 320.f, 0);
}