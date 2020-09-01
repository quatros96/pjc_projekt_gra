
#include "BulletUpdateComponent.h"
#include "WorldState.h"
#include "ScreenManagerRemoteControl.h"

void BulletUpdateComponent::spawnForPlayer(sf::Vector2f spawnPosition)
{
    m_MovingUp = true;
    m_BelongsToPlayer = true;
    m_IsSpawned = true;
    if(m_PlayerUpdateComponent->getLastDirection() == "up")
    {
        m_BulletGraphicsComponent->setRotation(90);
        m_RCC->setColliderRotation(90);
        m_TC->getLocation().x = spawnPosition.x + (m_PRCC->getSize().x / 2.f) + (m_TC->getSize().y / 2.f);
        //tweak y location for spawn
        m_TC->getLocation().y = spawnPosition.y - m_TC->getSize().x;
        m_Direction = "up";
    }
    else if(m_PlayerUpdateComponent->getLastDirection() == "down")
    {
        m_BulletGraphicsComponent->setRotation(-90);
        m_RCC->setColliderRotation(-90);
        m_TC->getLocation().x = spawnPosition.x + (m_PRCC->getSize().x / 2.f) - (m_TC->getSize().y / 2.f);
        //tweak y location for spawn
        m_TC->getLocation().y = spawnPosition.y + m_TC->getSize().x + m_RCC->getSize().y;
        m_Direction = "down";
    }
    else if(m_PlayerUpdateComponent->getLastDirection() == "left")
    {
        m_TC->getLocation().x = spawnPosition.x - m_TC->getSize().x;
        //tweak y location for spawn
        m_TC->getLocation().y = spawnPosition.y + (m_PRCC->getSize().y / 2.f) - (m_TC->getSize().y / 2.f);
        m_Direction = "left";
    }
    else if(m_PlayerUpdateComponent->getLastDirection() == "right")
    {
        m_BulletGraphicsComponent->setRotation(180);
        m_RCC->setColliderRotation(180);
        m_TC->getLocation().x = spawnPosition.x + m_PRCC->getSize().x + m_TC->getSize().x;
        //tweak y location for spawn
        m_TC->getLocation().y = spawnPosition.y + (m_PRCC->getSize().y / 2.f) + (m_TC->getSize().y / 2.f);
        m_Direction = "right";
    }
    //update collider
    m_RCC->setOrMoveCollider(m_TC->getLocation().x, m_TC->getLocation().y,
            m_TC->getSize().x, m_TC->getSize().y);
}
void BulletUpdateComponent::spawnForInvader(sf::Vector2f spawnPosition)
{
    m_MovingUp = false;
    m_BelongsToPlayer = false;
    m_IsSpawned = true;
    srand((int)time(0));
    m_AlienBulletSpeedModifier = ((rand() % m_ModifierRandomComponent)) + m_MinimumAdditionalModifier;
    m_TC->getLocation().x = spawnPosition.x;
    m_TC->getLocation().y = spawnPosition.y;
    m_RCC->setOrMoveCollider(m_TC->getLocation().x, m_TC->getLocation().y,
            m_TC->getSize().x, m_TC->getSize().y);
}
void BulletUpdateComponent::deSpawn()
{
    m_IsSpawned = false;
    m_TC->setLocation(sf::Vector2f(-100, 100));
    m_RCC->setOrMoveCollider(m_TC->getLocation().x, m_TC->getLocation().y,
        m_TC->getSize().x, m_TC->getSize().y);
	if(m_BulletGraphicsComponent->getRotation() != 0)
	{
        m_BulletGraphicsComponent->setRotation(0);
        m_RCC->setColliderRotation(0);
	}
	
}
bool BulletUpdateComponent::isMovingUp()
{
    return m_MovingUp;
}
void BulletUpdateComponent::update(float fps)
{
    if(m_IsSpawned)
    {
        if (m_BelongsToPlayer)
        {
            if(m_Direction == "up")
            {
                m_TC->getLocation().y -= m_Speed * fps;
            }
            else if(m_Direction == "down")
            {
                m_TC->getLocation().y += m_Speed * fps;
            }
            else if(m_Direction == "left")
            {
                m_TC->getLocation().x -= m_Speed * fps;
            }
            else
            {
                m_TC->getLocation().x += m_Speed * fps;
            }
        }
        else
        {
            m_TC->getLocation().y += m_Speed / m_AlienBulletSpeedModifier * fps;
        }
        m_RCC->setOrMoveCollider(m_TC->getLocation().x, m_TC->getLocation().y,
                                 m_TC->getSize().x, m_TC->getSize().y);
    }
}
