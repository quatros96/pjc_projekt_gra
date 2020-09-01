#pragma once

#include <memory>
#include "UpdateComponent.h"
#include "TransformComponent.h"
#include "GameObjectSharer.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

class BulletSpawner;

class InvaderUpdateComponent : public UpdateComponent
{
    std::string m_SpecificType{"invader"};
    std::shared_ptr<TransformComponent> m_TC;
    std::shared_ptr<RectColliderComponent> m_RCC;
    std::shared_ptr<TransformComponent> m_PlayerTC;
    std::shared_ptr<RectColliderComponent> m_PlayerRCC;
    BulletSpawner *m_BulletSpawner;
    float m_Speed{60.0f};
    float m_TimeSinceLastShot;
    float m_TimeBetweenShots{5.0f};
    float m_AccuracyModifier;
    float m_SpeedModifier{0.05};
    int m_RandSpeed;
public:
    void initializeBulletSpawner(BulletSpawner *bulletSpawner, int randSeed);
    void update(float fps) override;

    std::string getSpecificType()
    {

        return m_SpecificType;

    }

    void start(GameObjectSharer *gos, GameObject *self)
    {
        // Where is the player?
        m_PlayerTC = std::static_pointer_cast<TransformComponent>(
                gos->findFirstObjectWithTag("Player")
                        .getComponentByTypeAndSpecificType(
                                "transform", "transform"));
        m_PlayerRCC = std::static_pointer_cast<RectColliderComponent>(
                gos->findFirstObjectWithTag("Player")
                        .getComponentByTypeAndSpecificType(
                                "collider", "rect"));
        // Where is this specific invader
        m_TC = std::static_pointer_cast<TransformComponent>(
                self->getComponentByTypeAndSpecificType(
                        "transform", "transform"));
        m_RCC = std::static_pointer_cast<RectColliderComponent>(
                self->getComponentByTypeAndSpecificType(
                        "collider", "rect"));
    }
};
