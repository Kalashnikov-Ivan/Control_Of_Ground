#include "stdafx.h"

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
void SettingsContainer::InitGraphics(const std::string& path, const std::vector<sf::VideoMode>& videoModes)
{
	m_graphics = std::make_unique<GraphicsSettings>(path, videoModes);
}