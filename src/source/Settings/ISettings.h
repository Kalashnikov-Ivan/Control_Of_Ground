#ifndef I_SETTINGS_H
#define I_SETTINGS_H

#include <string>

namespace Settings
{
class ISettings
{
public:
	virtual bool loadFromFile(const std::string& path) = 0;
	virtual bool saveToFile(const std::string& path) = 0;
};
} // !namespace Settings

#endif // !I_SETTINGS_H