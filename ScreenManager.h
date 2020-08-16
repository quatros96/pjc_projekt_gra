//
// Created by quatr on 21.04.2020.
//

#ifndef GRA_SPACE_INVADERS_SCREENMANAGER_H
#define GRA_SPACE_INVADERS_SCREENMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include "GameScreen.h"
#include "ScreenManagerRemoteControl.h"
#include "SelectScreen.h"
#include "LevelManager.h"
#include "BitmapStore.h"
#include <iostream>

class ScreenManager : public ScreenManagerRemoteControl
{
private:
    std::map <std::string, std::unique_ptr<Screen>> m_Screens;
    LevelManager m_LevelManager;
protected:
    std::string m_CurrentScreen {"Select"};
public:
    BitmapStore m_BS;
    ScreenManager(sf::Vector2i res);
    void update(float fps);
    void draw(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window);


    void SwitchScreens(std::string screenTOSwitchTO)
    {
        m_CurrentScreen = "" + screenTOSwitchTO;
        m_Screens[m_CurrentScreen]->initalise();
    }
    void loadLevelInPlayMode(std::string screenToLoad)
    {
        m_LevelManager.getGameObjects().clear();
        m_LevelManager.loadGameObjectsForPlayMode(screenToLoad);
        SwitchScreens("Game");
    }
    std::vector<GameObject>& getGameObjects()
    {
        return m_LevelManager.getGameObjects();
    }
    GameObjectSharer& shareGameObjectSharer()
    {
        return m_LevelManager;
    }

};

#endif //GRA_SPACE_INVADERS_SCREENMANAGER_H
