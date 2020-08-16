//
// Created by quatr on 27.04.2020.
//

#include "PhysicsEnginePlayMode.h"
#include "developState.h"
#include "SoundEngine.h"
#include <iostream>
#include "WorldState.h"
#include "InvaderUpdateComponent.h"
#include "BulletUpdateComponent.h"

void PhysicsEnginePlayMode::detectInvaderCollisions(std::vector<GameObject> &objects,
        const std::vector<int> &bulletPositions)
{
    sf::Vector2f offScreen(-1, -1);
    auto invaderIt = objects.begin();
    auto invaderEnd = objects.end();
    for(invaderIt; invaderIt != invaderEnd; invaderIt++)
    {
        if((*invaderIt).isActive() && (*invaderIt).getTag() == "invader")
        {
            auto bulletIt = objects.begin();
            //jump to 1st bullet
            std::advance(bulletIt, bulletPositions[0]);
            auto bulletEnd = objects.end();
            for(bulletIt; bulletIt != bulletEnd; bulletIt++)
            {
                if((*invaderIt).getEncompassingRectCollider().
                    intersects((*bulletIt).getEncompassingRectCollider())
                    && (*bulletIt).getTag() == "bullet" &&
                    std::static_pointer_cast<BulletUpdateComponent>
                            ((*bulletIt).getUpdateComponent())->m_BelongsToPlayer)
                {
                    SoundEngine::playInvaderExplode();
                    (*invaderIt).getTransformComponent()->getLocation() = offScreen;
                    (*bulletIt).getTransformComponent()->getLocation() = offScreen;
                    WorldState::SCORE++;
                    WorldState::NUM_INVADERS--;
                    (*invaderIt).setInactive();
                }
            }
        }
    }
}
void PhysicsEnginePlayMode::detectPlayerCollisionsAndInvaderDirection(std::vector<GameObject>
        &objects, const std::vector<int> &bulletPositions)
{
    sf::Vector2f offScreen(-1, -1);
    sf::FloatRect playerCollider = m_Player->getEncompassingRectCollider();
    std::shared_ptr<TransformComponent> playerTransform = m_Player->getTransformComponent();
    sf::Vector2f playerLocation = playerTransform->getLocation();
    auto it3 = objects.begin();
    auto end3 = objects.end();
    for(it3; it3 != end3; it3++)
    {
        if((*it3).isActive() && (*it3).hasCollider() && (*it3).getTag() != "Player")
        {
            //get a reference to all parts we might need
            sf::FloatRect currentCollider = (*it3).getEncompassingRectCollider();
            //detect collisions with player
            if(currentCollider.intersects(playerCollider))
            {
                if((*it3).getTag() == "bullet")
                {
                    SoundEngine::playPlayerExplode();
                    WorldState::LIVES--;
                    (*it3).getTransformComponent()->getLocation() = offScreen;
                }
                if((*it3).getTag() == "invader")
                {
                    SoundEngine::playPlayerExplode();
                    SoundEngine::playInvaderExplode();
                    WorldState::LIVES--;
                    (*it3).getTransformComponent()->getLocation() = offScreen;
                    WorldState::SCORE++;
                    (*it3).setInactive();
                }
            }
            std::shared_ptr<TransformComponent> currentTransform =
                    (*it3).getTransformComponent();
            sf::Vector2f currentLocation = currentTransform->getLocation();
            std::string currentTag = (*it3).getTag();
            sf::Vector2f  currentSize = currentTransform->getSize();
            //handle direction and descent
            if(currentTag == "invader")
            {
                if(!m_NeedToDropDownAndReverse && !m_InvaderHitWallThisFrame)
                {
                    if(currentLocation.x >= WorldState::WORLD_WIDTH - currentSize.x)
                    {
                        if(std::static_pointer_cast<InvaderUpdateComponent>
                                ((*it3).getUpdateComponent())->isMovingRight())
                        {
                            m_InvaderHitWallThisFrame = true;
                        }
                    }
                    else if(currentLocation.x < 0)
                    {
                        if(!std::static_pointer_cast<InvaderUpdateComponent>
                                ((*it3).getUpdateComponent())->isMovingRight())
                        {
                            m_InvaderHitWallThisFrame = true;
                        }
                    }
                }
                else if(m_NeedToDropDownAndReverse && !m_InvaderHitWallPreviousFrame)
                {
                    if((*it3).hasUpdateComponent())
                    {
                        std::static_pointer_cast<InvaderUpdateComponent>
                                ((*it3).getUpdateComponent())->dropDownAndReverse();
                    }
                }
            }
        }
    }
}
void PhysicsEnginePlayMode::handleInvaderDirection()
{
    if(m_InvaderHitWallThisFrame)
    {
        m_NeedToDropDownAndReverse = true;
        m_InvaderHitWallThisFrame = false;
    }
    else
    {
        m_NeedToDropDownAndReverse = false;
    }
}
void PhysicsEnginePlayMode::initialize(GameObjectSharer &gos)
{
    m_PUC = std::static_pointer_cast<PlayerUpdateComponent>
            (gos.findFirstObjectWithTag("Player").getComponentByTypeAndSpecificType(
                    "update", "player"));
    m_Player = &gos.findFirstObjectWithTag("Player");
}
void PhysicsEnginePlayMode::detectCollisions(std::vector<GameObject> &objects,
        const std::vector<int> &bulletPositions)
{
    detectInvaderCollisions(objects, bulletPositions);
    detectPlayerCollisionsAndInvaderDirection(objects, bulletPositions);
    handleInvaderDirection();
}