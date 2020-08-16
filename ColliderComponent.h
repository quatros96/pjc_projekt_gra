//
// Created by quatr on 23.04.2020.
//

#ifndef GRA_SPACE_INVADERS_COLLIDERCOMPONENT_H
#define GRA_SPACE_INVADERS_COLLIDERCOMPONENT_H

#include "Component.h"
#include <iostream>

class ColliderComponent : public Component
{
private:
    std::string m_Type = "collider";
    bool m_Enabled {false};
public:
    std::string getType() override
    {
        return m_Type;
    }
    void disableComponent() override
    {
        m_Enabled = false;
    }
    void enableComponent() override
    {
        m_Enabled = true;
    }
    bool enabled() override
    {
        return m_Enabled;
    }
    void start(GameObjectSharer* gos, GameObject* self) override
    {

    }
};

#endif //GRA_SPACE_INVADERS_COLLIDERCOMPONENT_H
