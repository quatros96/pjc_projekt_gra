
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
                    getGlobalBounds().intersects((*bulletIt).getEncompassingRectCollider().getGlobalBounds())
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
    sf::RectangleShape playerCollider = m_Player->getEncompassingRectCollider();
    std::shared_ptr<TransformComponent> playerTransform = m_Player->getTransformComponent();
    sf::Vector2f playerLocation = playerTransform->getLocation();
    auto it3 = objects.begin();
    auto end3 = objects.end();
    for(it3; it3 != end3; it3++)
    {
        if((*it3).isActive() && (*it3).hasCollider() && (*it3).getTag() != "Player")
        {
            //get a reference to all parts we might need
            sf::RectangleShape currentCollider = (*it3).getEncompassingRectCollider();
            //detect collisions with player
            if(currentCollider.getGlobalBounds().intersects(playerCollider.getGlobalBounds()))
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

void PhysicsEnginePlayMode::handlePlayerWorldCollisions(std::vector<GameObject>& objects, std::shared_ptr<TileMap> map)
{
	//getting grid position
    x_start = m_PRCC->getWorldGridPosition().x - 1;
    x_end = m_PRCC->getWorldGridPosition().x + 3;
    y_start = m_PRCC->getWorldGridPosition().y - 1;
    y_end = m_PRCC->getWorldGridPosition().y + 3;
	//make sure that not checking outside map bounds
	if(x_start < 0)
	{
        x_start = 0;
	}
	else if(x_end > map->getMapSize().x)
	{
        x_end = map->getMapSize().x;
	}
    if (y_start < 0)
    {
        y_start = 0;
    }
    else if (y_end > map->getMapSize().y)
    {
        y_end = map->getMapSize().y;
    }
    
    for (int x = x_start; x < x_end; ++x)
    {
        for (int y = y_start; y < y_end; ++y)
        {
	        for (int k = 0; k < map->getMap()[x][y].size(); ++k)
	        {
                if (map->getMap()[x][y][k]->getCollisionStatus())
                {
                    sf::FloatRect playerBounds = m_PRCC->getColliderRectF().getGlobalBounds();
                    if (map->getMap()[x][y][k]->intersects(playerBounds))
                    {
                        sf::FloatRect obstacleBounds = map->getMap()[x][y][k]->getBounds();
                        //Bottom 
                        if (playerBounds.top < obstacleBounds.top
                            && playerBounds.top + playerBounds.height < obstacleBounds.top + obstacleBounds.height
                            && playerBounds.left < obstacleBounds.left + obstacleBounds.width
                            && playerBounds.left + playerBounds.width > obstacleBounds.left
                            && m_PUC->getLastDirection() == "down")
                        {
                            m_PTC->setLocation(sf::Vector2f(playerBounds.left - m_PRCC->getOffsets().x, obstacleBounds.top - playerBounds.height));
                        }

                        //Top 
                        else if (playerBounds.top > obstacleBounds.top
                            && playerBounds.top + playerBounds.height > obstacleBounds.top + obstacleBounds.height
                            && playerBounds.left < obstacleBounds.left + obstacleBounds.width
                            && playerBounds.left + playerBounds.width > obstacleBounds.left
                            && m_PUC->getLastDirection() == "up")
                        {
                            m_PTC->setLocation(sf::Vector2f(playerBounds.left - m_PRCC->getOffsets().x, obstacleBounds.top + obstacleBounds.height));
                        }

                        //Right
                        if (playerBounds.left < obstacleBounds.left
                            && playerBounds.left + playerBounds.width < obstacleBounds.left + obstacleBounds.width
                            && playerBounds.top < obstacleBounds.top + obstacleBounds.height
                            && playerBounds.top + playerBounds.height > obstacleBounds.top
                            && m_PUC->getLastDirection() == "right")
                        {
                            m_PTC->setLocation(sf::Vector2f(obstacleBounds.left - playerBounds.width - m_PRCC->getOffsets().x, playerBounds.top));
                        }

                        //Left
                        else if (playerBounds.left > obstacleBounds.left
                            && playerBounds.left + playerBounds.width > obstacleBounds.left + obstacleBounds.width
                            && playerBounds.top < obstacleBounds.top + obstacleBounds.height
                            && playerBounds.top + playerBounds.height > obstacleBounds.top
                            && m_PUC->getLastDirection() == "left")
                        {
                            m_PTC->setLocation(sf::Vector2f(obstacleBounds.left + obstacleBounds.width - m_PRCC->getOffsets().x, playerBounds.top));
                        }
                    }
                }
	        }
        }
    }
}

void PhysicsEnginePlayMode::handlePlayerWorldEdgeCollisions()
{
    if (m_PRCC->getPosition().x > WorldState::WORLD_WIDTH - m_PRCC->getSize().x)
    {
        m_PTC->getLocation().x = WorldState::WORLD_WIDTH - m_PRCC->getSize().x - m_PRCC->getOffsets().x;
    }
    else if (m_PRCC->getPosition().x < 0)
    {
        m_PTC->getLocation().x = -m_PRCC->getOffsets().x;
    }
    if (m_PTC->getLocation().y > WorldState::WORLD_HEIGHT - m_PTC->getSize().y)
    {
        m_PTC->getLocation().y = WorldState::WORLD_HEIGHT - m_PRCC->getSize().y - m_PRCC->getOffsets().y;
    }
    else if (m_PTC->getLocation().y < 0)
    {
        m_PTC->getLocation().y = -m_PRCC->getOffsets().y;
    }
}

void PhysicsEnginePlayMode::initialize(GameObjectSharer &gos)
{
    m_Player = &gos.findFirstObjectWithTag("Player");
    m_PUC = std::static_pointer_cast<PlayerUpdateComponent>
            (gos.findFirstObjectWithTag("Player").getComponentByTypeAndSpecificType(
                    "update", "player"));
    m_PRCC = std::static_pointer_cast<RectColliderComponent>(gos.findFirstObjectWithTag("Player").getComponentByTypeAndSpecificType("collider", "rect"));
    m_PTC = m_Player->getTransformComponent();
    x_start = 0;
    x_end = 0;
    y_start = 0;
    y_end = 0;
    layer = 0;
    
}
void PhysicsEnginePlayMode::detectCollisions(std::vector<GameObject> &objects,
        const std::vector<int> &bulletPositions, std::shared_ptr<TileMap> map)
{
    //detectInvaderCollisions(objects, bulletPositions);
    //detectPlayerCollisionsAndInvaderDirection(objects, bulletPositions);
    handlePlayerWorldCollisions(objects, map);
    handlePlayerWorldEdgeCollisions();
}