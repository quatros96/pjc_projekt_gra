#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include <fstream>
class SettingsManager
{
public:
	sf::VideoMode m_Resolution;
	bool m_FullScreen;
	unsigned m_FPSLimit;
	sf::ContextSettings m_ContextSettings;
	std::vector<sf::VideoMode> m_VideoModes;
	bool m_AutoMode;
	SettingsManager();
	void saveSettings(const std::string& filename);
	void loadSettings(const std::string& filename);
};

