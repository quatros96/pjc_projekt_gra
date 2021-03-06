
#include "PhysicsEnginePlayMode.h"
#include "developState.h"
#include "SoundEngine.h"
#include <iostream>
#include "WorldState.h"
#include "InvaderUpdateComponent.h"
#include "BulletUpdateComponent.h"

void PhysicsEnginePlayMode::detectEnemyCollisions(std::vector<GameObject> &objects,
        const std::vector<int> &bulletPositions)
{
    sf::Vector2f offScreen(-100, -100);
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
                    SoundEngine::playHit();
                    (*invaderIt).getTransformComponent()->getLocation() = offScreen;
                    (*bulletIt).getTransformComponent()->getLocation() = offScreen;
                    WorldState::SCORE++;
                    WorldState::NUM_INVADERS--;
                    (*invaderIt).setInactive();
                    (*invaderIt).getEncompassingRectCollider().setPosition(offScreen);
                }
            }
        }
    }
}
void PhysicsEnginePlayMode::detectPlayerCollisionsAndEnemy(std::vector<GameObject>
        &objects, const std::vector<int> &bulletPositions)
{
    sf::Time elapsed = clock.restart();
    sf::Vector2f offScreen(-100, -100);
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
                if((*it3).getTag() == "bullet" && !(std::static_pointer_cast<BulletUpdateComponent>
                    ((*it3).getUpdateComponent())->m_BelongsToPlayer))
                {
                    SoundEngine::playPlayerExplode();
                    WorldState::LIVES--;
                    (*it3).getTransformComponent()->getLocation() = offScreen;
                }
                if((*it3).getTag() == "invader" && std::static_pointer_cast<InvaderUpdateComponent>((*it3).getUpdateComponent())->canAttack())
                {
                    SoundEngine::playHit();
                    WorldState::LIVES--;
                    std::static_pointer_cast<InvaderUpdateComponent>((*it3).getUpdateComponent())->Attack();
                    //(*it3).getTransformComponent()->getLocation() = offScreen;
                    //WorldState::SCORE++;
                    //(*it3).setInactive();
                }
            }
        }
    }
}

void PhysicsEnginePlayMode::handlePlayerWorldCollisions(std::vector<GameObject>& objects, std::shared_ptr<TileMap>& map)
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

void PhysicsEnginePlayMode::handleBulletWorldEdgeCollisions(std::vector<GameObject>& objects,
    const std::vector<int>& bulletPositions)
{
    auto it3 = objects.begin();
    std::advance(it3, bulletPositions[0]);
    auto end3 = objects.end();
    for (it3; it3 != end3; it3++)
    {
        if ((*it3).isActive() && (*it3).hasCollider() && (*it3).getTag() == "bullet")
        {
            //get a reference to all parts
            sf::RectangleShape currentCollider = (*it3).getEncompassingRectCollider();
            auto bulletUpdateComp = std::dynamic_pointer_cast<BulletUpdateComponent>((*it3).getComponentByTypeAndSpecificType("update", "bullet"));
            //detect collisions with world edge
            if (currentCollider.getGlobalBounds().left + currentCollider.getGlobalBounds().width > WorldState::WORLD_WIDTH)
            {
                bulletUpdateComp->deSpawn();
                std::cout << "Bullet Despawned!" << std::endl;
                SoundEngine::playFireballExplode();
            }
            else if (currentCollider.getGlobalBounds().left < 0 && currentCollider.getGlobalBounds().left > -10)
            {
                bulletUpdateComp->deSpawn();
                std::cout << "Bullet Despawned!" << std::endl;
                SoundEngine::playFireballExplode();
            }
            else if(currentCollider.getGlobalBounds().top < 0 && currentCollider.getGlobalBounds().top > -10)
            {
                bulletUpdateComp->deSpawn();
                std::cout << "Bullet Despawned!" << std::endl;
                SoundEngine::playFireballExplode();
            }
            else if(currentCollider.getGlobalBounds().top > WorldState::WORLD_HEIGHT)
            {
                bulletUpdateComp->deSpawn();
                std::cout << "Bullet Despawned!" << std::endl;
                SoundEngine::playFireballExplode();
            }
        }
    }
}

void PhysicsEnginePlayMode::handleBulletWorldCollisions(std::vector<GameObject>& objects, std::shared_ptr<TileMap>& map,
	const std::vector<int>& bulletPositions)
{
    auto it3 = objects.begin();
    std::advance(it3, bulletPositions[0]);
    auto end3 = objects.end();
    for (it3; it3 != end3; it3++)
    {
        if ((*it3).isActive() && (*it3).hasCollider() && (*it3).getTag() == "bullet")
        {
            //get a reference to all parts
            sf::RectangleShape currentCollider = (*it3).getEncompassingRectCollider();
            auto bulletUpdateComp = std::dynamic_pointer_cast<BulletUpdateComponent>((*it3).getComponentByTypeAndSpecificType("update", "bullet"));
            auto bulletRectangleCollider = std::dynamic_pointer_cast<RectColliderComponent>((*it3).getComponentByTypeAndSpecificType("collider", "rect"));
        	if(!(bulletRectangleCollider->getWorldGridPosition().x > 100) && !(bulletRectangleCollider->getWorldGridPosition().y > 100))
        	{
                auto positionGrid = bulletRectangleCollider->getWorldGridPosition();
                for (auto tile : map->getMap()[positionGrid.x][positionGrid.y])
                {
                    if (tile->getCollisionStatus())
                    {
                        bulletUpdateComp->deSpawn();
                        std::cout << "Bullet Despawned!" << std::endl;
                        SoundEngine::playFireballExplode();
                    }
                }
        	}
        }
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
        const std::vector<int> &bulletPositions, std::shared_ptr<TileMap>& map)
{
    detectEnemyCollisions(objects, bulletPositions);
    detectPlayerCollisionsAndEnemy(objects, bulletPositions);
    handlePlayerWorldCollisions(objects, map);
    handlePlayerWorldEdgeCollisions();
    handleBulletWorldEdgeCollisions(objects, bulletPositions);
    handleBulletWorldCollisions(objects, map, bulletPositions);
}