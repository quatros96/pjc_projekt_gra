//
// Created by quatr on 27.04.2020.
//

#ifndef GRA_SPACE_INVADERS_GAMEOBJECTFACTORYPLAYMODE_H
#define GRA_SPACE_INVADERS_GAMEOBJECTFACTORYPLAYMODE_H

#include "GameObjectBlueprint.h"
#include "GameObject.h"
#include <vector>

class GameObjectFactoryPlayMode
{
public:
    void buildGameObject(GameObjectBlueprint& bp, std::vector<GameObject>& gameObjects);
};

#endif //GRA_SPACE_INVADERS_GAMEOBJECTFACTORYPLAYMODE_H
