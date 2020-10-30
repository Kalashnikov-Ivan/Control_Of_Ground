#include "stdafx.h"

#include "GraphicsSettings.h"

using namespace Settings;

//Constructors
GraphicsSettings::GraphicsSettings(const std::string& path) 
	: m_videoModes  { sf::VideoMode::getFullscreenModes() }
	, m_resolution  { sf::VideoMode::getDesktopMode()     }
	, m_fullscreen  { false }
	, m_vsync       { false }
	, m_framerateLimit { 60U }
	, m_context       { sf::ContextSettings() }
{
	if (!LoadFromFile(path))
		throw std::runtime_error("GraphicsSettings::Constructor: can't load from " + path);
}

//Constructors
GraphicsSettings::GraphicsSettings(const std::string& path, const std::vector<sf::VideoMode>& videoModes)
	: m_videoModes  { videoModes }
	, m_resolution  { sf::VideoMode::getDesktopMode() }
	, m_fullscreen  { false }
	, m_vsync       { false }
	, m_framerateLimit { 60U }
	, m_context     { sf::ContextSettings() }
{
	if (!LoadFromFile(path))
		throw std::runtime_error("GraphicsSettings::Constructor: can't load from " + path);
}

GraphicsSettings::GraphicsSettings(std::vector<sf::VideoMode> videoModes, const sf::VideoMode& resolution,
								   const bool fullscreen, const bool vsync, const unsigned int framerate_limit,
								   const sf::ContextSettings& context)
	: m_videoModes   { videoModes }
	, m_resolution   { resolution }
	, m_fullscreen   { fullscreen }
	, m_vsync	     { vsync }
	, m_framerateLimit { framerate_limit }
	, m_context      { context }
{

}

GraphicsSettings::~GraphicsSettings()
{

}

//Loader
bool GraphicsSettings::LoadFromFile(const std::string& path)
{
	std::ifstream graphicsInIfs{ path };
	if (graphicsInIfs.is_open())
	{
		std::string option{ "" };
		while (graphicsInIfs >> option)
		{
			if (option == "VIDEO_MODE")
			{
				graphicsInIfs >> m_resolution.width;
				graphicsInIfs >> m_resolution.height;
			}
			else if (option == "FRAMERATE")
				graphicsInIfs >> m_framerateLimit;
			else if (option == "ANTIALISING")
				graphicsInIfs >> m_context.antialiasingLevel;
			else if (option == "FULLSCREEN")
				graphicsInIfs >> m_fullscreen;
			else if (option == "VERTICAL_SYNC")
				graphicsInIfs >> m_vsync;
		}
	}
	else
	{
		std::cerr << path << "cannot open..." << std::endl
						  << "Using default settings..." << std::endl;

		graphicsInIfs.close();
		return false;
	}
	graphicsInIfs.close();
	return true;
}

bool GraphicsSettings::SaveToFile(const std::string& path)
{
	std::ofstream graphicsIniOfs{ path };
	if (graphicsIniOfs.is_open())
	{
		graphicsIniOfs << "VIDEO_MODE" << m_resolution.width << ' ' << m_resolution.height << std::endl;
		graphicsIniOfs << "FRAMERATE" << m_framerateLimit << std::endl;
		graphicsIniOfs << "ANTIALISING" << m_context.antialiasingLevel << std::endl;
		graphicsIniOfs << "FULLSCREEN" << m_fullscreen << std::endl;
		graphicsIniOfs << "VERTICAL_SYNC" << m_vsync << std::endl;
	}
	else
	{
		std::cerr << path << "cannot open..." << std::endl;

		graphicsIniOfs.close();
		return false;
	}
	graphicsIniOfs.close();
	return true;
}