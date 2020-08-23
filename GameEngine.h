//
// Created by quatr on 21.04.2020.
//

#ifndef GRA_SPACE_INVADERS_GAMEENGINE_H
#define GRA_SPACE_INVADERS_GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include "ScreenManager.h"
#include "SoundEngine.h"
#include "SettingsManager.h"

class GameEngine
{
private:
    sf::Clock m_Clock;
    sf::Time m_DT;
    sf::RenderWindow m_Window;
    std::unique_ptr<ScreenManager> m_ScreenManager;
    SettingsManager m_SettingsManager;
	
    float m_FPS {};
    sf::Vector2f m_Resolution;
    void handleInput();
    void update();
    void draw();

public:
    void initSettings();
    SoundEngine m_SoundEngine;
    GameEngine();
    void run();
};

#endif //GRA_SPACE_INVADERS_GAMEENGINE_H
