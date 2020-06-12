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
	GraphicsSettings(const std::string& path, const std::vector<sf::VideoMode>& video_modes);
	GraphicsSettings(std::vector<sf::VideoMode> video_modes, const sf::VideoMode& resolution,
					 const bool fullscreen = false, const bool vsync = false, const unsigned int framerate_limit = 60U,
					 const sf::ContextSettings& context = sf::ContextSettings());
	~GraphicsSettings();

	//Loader
	virtual bool loadFromFile(const std::string& path) override;
	virtual bool saveToFile(const std::string& path)   override;

	std::vector<sf::VideoMode> m_video_modes;

	sf::VideoMode m_resolution;
	bool m_fullscreen;
	bool m_vsync;
	unsigned int m_framerate_limit;
	sf::ContextSettings m_context;
	
private:

};
} // !namespace Settings
#endif // !GRAPHTICS_SETTINGS_H
