#pragma once

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
    int getRotation();
};

