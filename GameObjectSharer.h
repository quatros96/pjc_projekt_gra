//
// Created by quatr on 27.04.2020.
//

#ifndef GRA_SPACE_INVADERS_GAMEOBJECTSHARER_H
#define GRA_SPACE_INVADERS_GAMEOBJECTSHARER_H

#include <vector>
#include <string>

class GameObject;

class GameObjectSharer
{
public:
    virtual std::vector<GameObject>& getGameObjectsWithGOS() = 0;
    virtual GameObject& findFirstObjectWithTag(std::string tag) = 0;
};

#endif //GRA_SPACE_INVADERS_GAMEOBJECTSHARER_H
