#include "SettingsManager.h"

SettingsManager::SettingsManager()
{
	m_Resolution = sf::VideoMode::getDesktopMode();
	m_FullScreen = true;
	m_FPSLimit = 120;
	m_ContextSettings.antialiasingLevel = 0;
	m_VideoModes = sf::VideoMode::getFullscreenModes();
}

void SettingsManager::saveSettings(const std::string& filename)
{
	std::ofstream ofs("settings/" + filename);
	if (ofs.is_open())
	{
		ofs << m_AutoMode;
		ofs << m_Resolution.width;
		ofs << m_Resolution.height;
		ofs << m_FullScreen;
		ofs << m_FPSLimit;
		ofs << m_ContextSettings.antialiasingLevel;
	}
	ofs.close();
}

void SettingsManager::loadSettings(const std::string& filename)
{
	std::ifstream ifs("settings/" + filename);
	if(ifs.is_open())
	{
		ifs >> m_AutoMode;
		ifs >> m_Resolution.width;
		ifs >> m_Resolution.height;
		ifs >> m_FullScreen;
		ifs >> m_FPSLimit;
		ifs >> m_ContextSettings.antialiasingLevel;
	}
	ifs.close();
}
