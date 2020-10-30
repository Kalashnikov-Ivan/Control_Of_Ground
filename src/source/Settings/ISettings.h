#ifndef I_SETTINGS_H
#define I_SETTINGS_H

#include <string>

namespace Settings
{
class ISettings
{
public:
	virtual bool LoadFromFile(const std::string& path) = 0;
	virtual bool SaveToFile(const std::string& path)   = 0;
};
} // !namespace Settings

#endif // !I_SETTINGS_H