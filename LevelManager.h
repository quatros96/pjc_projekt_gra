#pragma once

#include "GameObject.h"
#include <vector>
#include <string>
#include "GameObjectSharer.h"

class LevelManager : public GameObjectSharer
{
private:
    std::vector<GameObject> m_GameObjects;
    const std::string WORLD_FOLDER {"world"};
    const std::string SLASH {"/"};
    void runStartPhase();
    void activateAllGameObjects();

public:
    std::vector<GameObject>& getGameObjects();
    void loadGameObjectsForPlayMode(std::string screenToLoad);
    std::vector<GameObject>& getGameObjectsWithGOS()
    {
        return m_GameObjects;
    }
    GameObject& findFirstObjectWithTag(std::string tag)
    {
        auto it = m_GameObjects.begin();
        auto end = m_GameObjects.end();
        for(it; it != end; it++)
        {
            if((*it).getTag() == tag)
            {
                return (*it);
            }
        }
#ifdef  debuggingOnConsole
        std::cout <<
        "LevelManager.h findFirstGameObjectWithTag() "
        << "- TAG NOT FOUND ERROR!"
        << endl;
#endif
        return m_GameObjects[0];
    }
};
