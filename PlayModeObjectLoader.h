//
// Created by quatr on 27.04.2020.
//

#ifndef GRA_SPACE_INVADERS_PLAYMODEOBJECTLOADER_H
#define GRA_SPACE_INVADERS_PLAYMODEOBJECTLOADER_H

#include <vector>
#include <string>
#include "GameObject.h"
#include "BlueprintObjectParser.h"
#include "GameObjectFactoryPlayMode.h"

class PlayModeObjectLOader
{
private:
    BlueprintObjectParser m_BOP;
    GameObjectFactoryPlayMode m_GameObjectFactoryPlayMode;
public:
    void loadGameObjectsForPlayMode(std::string pathToFile, std::vector<GameObject>& mGameObjects);
};

#endif //GRA_SPACE_INVADERS_PLAYMODEOBJECTLOADER_H
