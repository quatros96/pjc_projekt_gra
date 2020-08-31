
#include "PlayModeObjectLoader.h"
#include "ObjectTags.h"
#include <iostream>
#include <fstream>

void PlayModeObjectLOader::loadGameObjectsForPlayMode(std::string pathToFile,
        std::vector<GameObject> &mGameObjects)
{
    std::ifstream reader(pathToFile);
    std::string lineFromFile;
    float x = 0, y = 0, width = 0, height = 0;
    std::string value {};
    while(std::getline(reader, lineFromFile))
    {
        if(lineFromFile.find(ObjectTags::START_OF_OBJECT) != std::string::npos)
        {
            GameObjectBlueprint bp;
            m_BOP.parseNextObjectForBlueprint(reader, bp);
            m_GameObjectFactoryPlayMode.buildGameObject(bp, mGameObjects);
        }
    }
}