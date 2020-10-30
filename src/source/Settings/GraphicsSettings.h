#ifndef GRAPHTICS_SETTINGS_H
#define GRAPHTICS_SETTINGS_H

#include "ISettings.h"

namespace Settings
{
class GraphicsSettings :
	public ISettings
{
public:
	GraphicsSettings(const std::string& path);
	GraphicsSettings(const std::string& path, const std::vector<sf::VideoMode>& videoModes);
	GraphicsSettings(std::vector<sf::VideoMode> videoModes, const sf::VideoMode& resolution,
					 const bool fullscreen = false, const bool vsync = false, const unsigned int framerateLimit = 60U,
					 const sf::ContextSettings& context = sf::ContextSettings());
	~GraphicsSettings();

//Loader
	virtual bool LoadFromFile(const std::string& path) override;
	virtual bool SaveToFile(const std::string& path)   override;

	std::vector<sf::VideoMode> m_videoModes;

	sf::VideoMode m_resolution;
	bool m_fullscreen;
	bool m_vsync;
	unsigned int m_framerateLimit;
	sf::ContextSettings m_context;
};
} // !namespace Settings
#endif // !GRAPHTICS_SETTINGS_H
