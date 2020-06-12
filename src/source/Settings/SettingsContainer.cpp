#include "stdHeader.hpp"

#include "SettingsContainer.h"

using namespace Settings;

SettingsContainer::SettingsContainer()
	: m_graphics{ nullptr }
{

}

SettingsContainer::~SettingsContainer()
{
	if (m_graphics)
		delete m_graphics;
}

//Init
void SettingsContainer::initGraphics(const std::string& path, const std::vector<sf::VideoMode>& video_modes)
{
	m_graphics = new GraphicsSettings(path, video_modes);
}