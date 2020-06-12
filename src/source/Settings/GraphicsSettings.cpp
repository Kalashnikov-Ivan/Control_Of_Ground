#include "stdHeader.hpp"

#include "GraphicsSettings.h"

using namespace Settings;

//Constructors
GraphicsSettings::GraphicsSettings(const std::string& path) 
	: m_video_modes { sf::VideoMode::getFullscreenModes() },
	m_resolution    { sf::VideoMode::getDesktopMode()     },
	m_fullscreen    { false },
	m_vsync         { false },
	m_framerate_limit { 60U },
	m_context       { sf::ContextSettings() }
{
	loadFromFile(path);
}

//Constructors
GraphicsSettings::GraphicsSettings(const std::string& path, const std::vector<sf::VideoMode>& video_modes)
	: m_video_modes  { video_modes },
	m_resolution     { sf::VideoMode::getDesktopMode() },
	m_fullscreen     { false },
	m_vsync          { false },
	m_framerate_limit{ 60U },
	m_context        { sf::ContextSettings() }
{
	loadFromFile(path);
}

GraphicsSettings::GraphicsSettings(std::vector<sf::VideoMode> video_modes, const sf::VideoMode& resolution,
								   const bool fullscreen, const bool vsync, const unsigned int framerate_limit,
								   const sf::ContextSettings& context)
	: m_video_modes   { video_modes },
	m_resolution      { resolution },
	m_fullscreen      { fullscreen },
	m_vsync	          { vsync },
	m_framerate_limit { framerate_limit },
	m_context         { context }
{

}

GraphicsSettings::~GraphicsSettings()
{

}

//Loader
bool GraphicsSettings::loadFromFile(const std::string& path)
{
	std::ifstream graphics_ini_ifs{ path };
	if (graphics_ini_ifs.is_open())
	{
		std::string option{ "" };
		while (graphics_ini_ifs >> option)
		{
			if (option == "VIDEO_MODE")
			{
				graphics_ini_ifs >> m_resolution.width;
				graphics_ini_ifs >> m_resolution.height;
			}
			else if (option == "FRAMERATE")
				graphics_ini_ifs >> m_framerate_limit;
			else if (option == "ANTIALISING")
				graphics_ini_ifs >> m_context.antialiasingLevel;
			else if (option == "FULLSCREEN")
				graphics_ini_ifs >> m_fullscreen;
			else if (option == "VERTICAL_SYNC")
				graphics_ini_ifs >> m_vsync;
		}
	}
	else
	{
		std::cerr << path << "cannot open..." << std::endl
						  << "Using default settings..." << std::endl;

		graphics_ini_ifs.close();
		return false;
	}
	graphics_ini_ifs.close();
	return true;
}

bool GraphicsSettings::saveToFile(const std::string& path)
{
	std::ofstream graphics_ini_ofs{ path };
	if (graphics_ini_ofs.is_open())
	{
		graphics_ini_ofs << "VIDEO_MODE" << m_resolution.width << ' ' << m_resolution.height << std::endl;
		graphics_ini_ofs << "FRAMERATE" << m_framerate_limit << std::endl;
		graphics_ini_ofs << "ANTIALISING" << m_context.antialiasingLevel << std::endl;
		graphics_ini_ofs << "FULLSCREEN" << m_fullscreen << std::endl;
		graphics_ini_ofs << "VERTICAL_SYNC" << m_vsync << std::endl;
	}
	else
	{
		std::cerr << path << "cannot open..." << std::endl;

		graphics_ini_ofs.close();
		return false;
	}
	graphics_ini_ofs.close();
	return true;
}