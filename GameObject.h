//
// Created by quatr on 23.04.2020.
//

#ifndef GRA_SPACE_INVADERS_GAMEOBJECT_H
#define GRA_SPACE_INVADERS_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Component.h"
#include "GraphicsComponent.h"
#include "GameObjectSharer.h"
#include "UpdateComponent.h"

class GameObject
{
private:
    std::vector<std::shared_ptr<Component>> m_Components;
    std::string m_Tag;
    bool m_Active {false};
    int m_NumberUpdateComponents {};
    bool m_HasUpdateComponent {false};
    int m_FirstUpdateComponentLocation {-1};
    int m_GraphicsComponentLocation {-1};
    bool m_HasGraphicsComponent {false};
    int m_TransformComponentLocation {-1};
    int m_NumberRectColliderComponents {};
    int m_FirstRectColliderComponentLocation {-1};
    bool m_HasCollider {false};
public:
    void update(float fps);
    void draw(sf::RenderWindow& window);
    void addComponent(std::shared_ptr<Component> component);
    void setActive();
    void setInactive();
    bool isActive();
    void setTag(std::string tag);
    std::string getTag();
    void start(GameObjectSharer* gos);
    std::shared_ptr<Component> getComponentByTypeAndSpecificType(std::string type,
            std::string sepcificType);
    sf::FloatRect& getEncompassingRectCollider();
    bool hasCollider();
    bool hasUpdateComponent();
    std::string getEncompassingRectColliderTag();
    std::shared_ptr<GraphicsComponent> getGraphicsComponent();
    std::shared_ptr<TransformComponent> getTransformComponent();
    std::shared_ptr<UpdateComponent> getUpdateComponent();
};

#endif //GRA_SPACE_INVADERS_GAMEOBJECT_H
