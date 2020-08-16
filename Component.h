//
// Created by quatr on 23.04.2020.
//

#ifndef GRA_SPACE_INVADERS_COMPONENT_H
#define GRA_SPACE_INVADERS_COMPONENT_H

#include "GameObjectSharer.h"
#include <string>

class GameObject;

class Component
{
public:
    virtual std::string getType() = 0;
    virtual std::string getSpecificType() = 0;
    virtual void disableComponent() = 0;
    virtual void enableComponent() = 0;
    virtual bool enabled() = 0;
    virtual void start(GameObjectSharer* gos, GameObject* self) = 0;
};

#endif //GRA_SPACE_INVADERS_COMPONENT_H
