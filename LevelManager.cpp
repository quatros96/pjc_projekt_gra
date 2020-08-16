//
// Created by quatr on 27.04.2020.
//

#include "LevelManager.h"
#include "PlayModeObjectLoader.h"
#include <iostream>

void LevelManager::loadGameObjectsForPlayMode(std::string screenToLoad)
{
    m_GameObjects.clear();
    std::string levelToLoad = "" + WORLD_FOLDER + SLASH + screenToLoad;
    PlayModeObjectLOader pmol;
    pmol.loadGameObjectsForPlayMode(levelToLoad, m_GameObjects);
    runStartPhase();
}
std::vector<GameObject>& LevelManager::getGameObjects()
{
    return m_GameObjects;
}
void LevelManager::runStartPhase()
{
    auto it = m_GameObjects.begin();
    auto end = m_GameObjects.end();
    for(it; it != end; it++)
    {
        (*it).start(this);
    }
    activateAllGameObjects();
}
void LevelManager::activateAllGameObjects()
{
    auto it = m_GameObjects.begin();
    auto end = m_GameObjects.end();
    for(it; it != end; it++)
    {
        (*it).setActive();
    }
}