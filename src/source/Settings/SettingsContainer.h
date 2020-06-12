#ifndef SETTINGS_CONTAINER_H
#define SETTINGS_CONTAINER_H

#include "GraphicsSettings.h"

namespace Settings
{
class SettingsContainer
{
public:
	SettingsContainer();
	~SettingsContainer();

	//Init
	void initGraphics(const std::string& path, const std::vector<sf::VideoMode>& video_modes);

	GraphicsSettings* m_graphics;
private:

};
} // !namespace Settings
#endif // !SETTINGS_CONTAINER_H