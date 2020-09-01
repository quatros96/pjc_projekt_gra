#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObjectSharer.h"

class GraphicsComponent : public Component
{
private:
    std::string m_Type {"graphics"};
    bool m_Enabled = false;
public:
    virtual void draw(sf::RenderWindow& window, std::shared_ptr<TransformComponent> t) = 0;
    virtual void initializeGraphics(std::string bitmapName, sf::Vector2f objectSize) = 0;
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
