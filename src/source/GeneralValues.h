#ifndef GENERAL_VALUES_H
#define GENERAL_VALUES_H

#include "Settings/SettingsContainer.h"

class GeneralValues
{
public:
	GeneralValues() : window { nullptr }
	{}
	~GeneralValues()
	{}

	//Settings
	Settings::SettingsContainer settings;

	//Window
	sf::RenderWindow* window;

	//Supported keys
	std::map<const std::string, int> supported_keys;

	//Fonts
	std::map<const std::string, sf::Font*> supported_fonts;
};

#endif // !GENERAL_VALUES_H