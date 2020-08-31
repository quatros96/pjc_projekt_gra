
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
        m_TC->getLocation().x = spawnPosition.x;
        //tweak y location for spawn
        m_TC->getLocation().y = spawnPosition.y - m_TC->getSize().y;
        m_Direction = "up";
    }
    else if(m_PlayerUpdateComponent->getLastDirection() == "down")
    {
        m_TC->getLocation().x = spawnPosition.x;
        //tweak y location for spawn
        m_TC->getLocation().y = spawnPosition.y + 3 * m_TC->getSize().y;
        m_Direction = "down";
    }
    else if(m_PlayerUpdateComponent->getLastDirection() == "left")
    {
        m_TC->getLocation().x = spawnPosition.x;
        //tweak y location for spawn
        m_TC->getLocation().y = spawnPosition.y + 3 * m_TC->getSize().y;
        m_Direction = "left";
        m_BulletGraphicsComponent->setRotation(90);
    }
    else if(m_PlayerUpdateComponent->getLastDirection() == "right")
    {
        m_TC->getLocation().x = spawnPosition.x;
        //tweak y location for spawn
        m_TC->getLocation().y = spawnPosition.y + 3 * m_TC->getSize().y;
        m_Direction = "right";
        m_BulletGraphicsComponent->setRotation(90);
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
	if(m_Direction == "left" || m_Direction == "right")
	{
        m_BulletGraphicsComponent->setRotation(-90);
	}
    else
		m_BulletGraphicsComponent->setRotation(0);
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
        if (m_TC->getLocation().y > WorldState::WORLD_HEIGHT || m_TC->getLocation().y < -2)
        {
            deSpawn();
        }
        m_RCC->setOrMoveCollider(m_TC->getLocation().x, m_TC->getLocation().y,
                                 m_TC->getSize().x, m_TC->getSize().y);
    }
}
