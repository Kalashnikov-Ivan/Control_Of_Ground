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
	void InitGraphics(const std::string& path, const std::vector<sf::VideoMode>& videoModes);

	std::unique_ptr<GraphicsSettings> m_graphics;
private:

};
} // !namespace Settings
#endif // !SETTINGS_CONTAINER_H