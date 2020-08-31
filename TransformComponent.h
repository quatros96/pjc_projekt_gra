//
// Created by quatr on 23.04.2020.
//

#ifndef GRA_SPACE_INVADERS_TRANSFORMCOMPONENT_H
#define GRA_SPACE_INVADERS_TRANSFORMCOMPONENT_H

#include "Component.h"
#include <SFML/Graphics.hpp>

class TransformComponent : public Component
{
private:
    const std::string m_Type = "transform";
    sf::Vector2f m_Location;
    float m_Height;
    float m_Width;
    float m_Rotation;
    float m_Speed;
    float m_Acceleration = 25.0;
    float m_CurrSpeed = 0;
public:
    TransformComponent(float width, float height, sf::Vector2f location, float speed);
    void moveLeft(float dt);
    void moveRight(float dt);
    void moveUp(float dt);
    void moveDown(float dt);
    void decelerate(float dt);
    sf::Vector2f& getLocation();
    void setLocation(sf::Vector2f position);
    sf::Vector2f getSize();
    std::string getType()
    {
        return m_Type;
    }
    std::string getSpecificType()
    {
        return m_Type;
    }
    void disableComponent() {};
    void enableComponent() {};
    bool enabled()
    {
        return false;
    }
    void start(GameObjectSharer* gos, GameObject* self) {};
};

inline void TransformComponent::decelerate(float dt)
{
	if(m_CurrSpeed > 0)
	{
        m_CurrSpeed -= 0.5 * m_Acceleration * dt;
	}
}

#endif //GRA_SPACE_INVADERS_TRANSFORMCOMPONENT_H
