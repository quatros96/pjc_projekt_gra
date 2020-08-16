//
// Created by quatr on 23.04.2020.
//

#ifndef GRA_SPACE_INVADERS_RECTCOLLIDERCOMPONENT_H
#define GRA_SPACE_INVADERS_RECTCOLLIDERCOMPONENT_H

#include "ColliderComponent.h"
#include <SFML/Graphics.hpp>

class RectColliderComponent : public ColliderComponent
{
private:
    std::string m_SpecificType = "rect";
    sf::FloatRect m_Collider;
    std::string m_Tag = "";
public:
    RectColliderComponent(std::string name);
    std::string getColliderTag();
    void setOrMoveCollider(float x, float y, float width, float height);
    sf::FloatRect & getColliderRectF();
    std::string getSpecificType() override
    {
        return m_SpecificType;
    }
    void start(GameObjectSharer* gos, GameObject* self)
    {

    }
};

#endif //GRA_SPACE_INVADERS_RECTCOLLIDERCOMPONENT_H
