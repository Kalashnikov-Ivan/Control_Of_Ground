#include "stdHeader.hpp"

#include "SettingsContainer.h"

using namespace Settings;

SettingsContainer::SettingsContainer()
	: m_graphics{ nullptr }
{

}

SettingsContainer::~SettingsContainer()
{
}

//Init
void SettingsContainer::initGraphics(const std::string& path, const std::vector<sf::VideoMode>& video_modes)
{
	m_graphics = std::make_unique<GraphicsSettings>(path, video_modes);
}