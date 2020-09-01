#pragma once

#include <memory>
#include "UpdateComponent.h"
#include "TransformComponent.h"
#include "GameObjectSharer.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

#include "AnimatedGraphicsComponent.h"

class PlayerUpdateComponent : public UpdateComponent
{
private:
    std::string m_SpecificType = "player";
    std::shared_ptr<TransformComponent> m_TC;
    std::shared_ptr<RectColliderComponent> m_RCC;
    std::shared_ptr<AnimatedGraphicsComponent> m_AGC;
    float m_Speed = 50.0f;
    float m_XExtent {0};
    float m_YExtent {0};
    bool m_IsHoldingLeft = false;
    bool m_IsHoldingRight = false;
    bool m_IsHoldingUp = false;
    bool m_IsHoldingDown = false;
    bool m_SpaceClicked = false;
    std::string m_lastDirection;
public:
    void updateShipTravelWithController(float x, float y);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();
    void attack();
    void stopAttack();

    std::string getLastDirection()
    {
        return m_lastDirection;
    }
    std::string getSpecificType()
    {
        return m_SpecificType;
    }
    void start(GameObjectSharer* gos, GameObject* self) override
    {
        m_TC = std::static_pointer_cast<TransformComponent>(
                self->getComponentByTypeAndSpecificType(
                        "transform", "transform"));
        m_RCC = std::static_pointer_cast<RectColliderComponent>(
                self->getComponentByTypeAndSpecificType(
                        "collider", "rect"));
        
        m_AGC = std::static_pointer_cast<AnimatedGraphicsComponent>(
            gos->findFirstObjectWithTag("Player")
            .getComponentByTypeAndSpecificType(
                "graphics", "animated"));
        
    	
    }
    void update(float fps) override;
};
