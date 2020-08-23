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
    sf::RectangleShape m_Collider;
    std::string m_Tag = "";
    float m_HeightOffset = 0;
    float m_WidthOffset = 0;
public:
    RectColliderComponent(std::string name, float widthOffset, float heightOffset);
    std::string getColliderTag();
    void setOrMoveCollider(float x, float y, float width, float height);
    sf::RectangleShape & getColliderRectF();
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    sf::Vector2f getOffsets();
    std::string getSpecificType() override
    {
        return m_SpecificType;
    }
    void start(GameObjectSharer* gos, GameObject* self)
    {

    }
};

#endif //GRA_SPACE_INVADERS_RECTCOLLIDERCOMPONENT_H
