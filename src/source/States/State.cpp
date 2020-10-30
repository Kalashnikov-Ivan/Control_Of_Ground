#include "stdafx.h"

#include "State.hpp"

using namespace States;

// Constructors
State::State(StateContext& ctx)
	: m_stateContext { ctx }
	, m_quit         { false }
	, m_paused       { false }
{
}
State::~State()
{
}

// Accessors
const bool State::GetQuit() const
{
	return m_quit;
}

std::string State::GetStringInfoMouse()
{
	std::stringstream result;

	result << "x: " << m_mousePosView.x << " " << "y: " << m_mousePosView.y << '\n';
	result << "" << m_mousePosGrid.x << " " << "" << m_mousePosGrid.y << '\n';

	return result.str();
}

// Info
std::string States::State::GetStringMousePos() const
{
	std::stringstream result;

	result << "mouse x = " << m_mousePosView.x << " " << "y = " << m_mousePosView.y << '\n';

	return result.str();
}

// Functions
void States::State::Pause()
{
	m_paused = true;
}

void States::State::Unpause()
{
	m_paused = false;
}

void State::Reset(const sf::VideoMode& vm)
{

}

void State::QuitState()
{
	m_quit = true;
}

void State::UpdateMousePos()
{
	m_mousePosScreen = sf::Mouse::getPosition();
	m_mousePosWindow = sf::Mouse::getPosition(m_stateContext.window);
	m_mousePosView = m_stateContext.window.mapPixelToCoords(sf::Mouse::getPosition(m_stateContext.window));
	m_mousePosGrid = sf::Vector2u(
		static_cast<unsigned>(m_mousePosView.x / m_stateContext.gridSze.x), 
		static_cast<unsigned>(m_mousePosView.y / m_stateContext.gridSze.y)
		);
}