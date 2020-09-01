#pragma once

#include <memory>
#include "UpdateComponent.h"
#include "TransformComponent.h"
#include "GameObjectSharer.h"
#include "RectColliderComponent.h"
#include "GameObject.h"
#include "PlayerUpdateComponent.h"
#include "StandardGraphicsComponent.h"

class BulletUpdateComponent : public UpdateComponent
{
private:
    std::string m_SpecificType = "bullet";
    std::shared_ptr<TransformComponent> m_TC;
    std::shared_ptr<RectColliderComponent> m_RCC;
    std::shared_ptr<PlayerUpdateComponent> m_PlayerUpdateComponent;
    std::shared_ptr<StandardGraphicsComponent> m_BulletGraphicsComponent;
    std::shared_ptr<RectColliderComponent> m_PRCC;
    float m_Speed {200.0f};

    int m_AlienBulletSpeedModifier;
    int m_ModifierRandomComponent = 5;
    int m_MinimumAdditionalModifier {5};
    bool m_MovingUp {true};
    std::string m_Direction {};
public:
    bool m_BelongsToPlayer {false};
    bool m_IsSpawned {false};
    void spawnForPlayer(sf::Vector2f spawnPosition);
    void spawnForInvader(sf::Vector2f spawnPosition);
    void deSpawn();
    bool isMovingUp();
    std::string getSpecificType()
    {
        return m_SpecificType;
    }
    void start(GameObjectSharer* gos, GameObject* self)
    {
        // Where is this specific invader
        m_TC = std::static_pointer_cast<TransformComponent>(
                self->getComponentByTypeAndSpecificType(
                        "transform", "transform"));

        m_RCC = std::static_pointer_cast<RectColliderComponent>(
                self->getComponentByTypeAndSpecificType(
                        "collider", "rect"));

        m_PlayerUpdateComponent = std::static_pointer_cast<PlayerUpdateComponent>(
                gos->findFirstObjectWithTag("Player")
                        .getComponentByTypeAndSpecificType(
                                "update", "player"));

        m_BulletGraphicsComponent = std::static_pointer_cast<StandardGraphicsComponent>
                (self->getComponentByTypeAndSpecificType("graphics", "standard"));
    	m_PRCC = std::static_pointer_cast<RectColliderComponent>(
            gos->findFirstObjectWithTag("Player")
            .getComponentByTypeAndSpecificType(
                "collider", "rect"));
    }
    void update(float fps) override;
};
