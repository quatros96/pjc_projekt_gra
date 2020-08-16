//
// Created by quatr on 23.04.2020.
//

#ifndef GRA_SPACE_INVADERS_STANDARDGRAPHICSCOMPONENT_H
#define GRA_SPACE_INVADERS_STANDARDGRAPHICSCOMPONENT_H

#include "Component.h"
#include "GraphicsComponent.h"
#include <string>

class Component;

class StandardGraphicsComponent : public GraphicsComponent
{
private:
    sf::Sprite m_Sprite;
    std::string m_SpecificType = "standard";
public:
    std::string getSpecificType()
    {
        return m_SpecificType;
    }
    void start(GameObjectSharer* gos, GameObject* self)
    {

    }
    void draw(sf::RenderWindow& window, std::shared_ptr<TransformComponent> t) override;
    void initializeGraphics(std::string bitmapName, sf::Vector2f objectSize) override;
    void setRotation(float angle);
};

#endif //GRA_SPACE_INVADERS_STANDARDGRAPHICSCOMPONENT_H
