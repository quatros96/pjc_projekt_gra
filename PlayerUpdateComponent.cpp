//
// Created by quatr on 23.04.2020.
//

#include "PlayerUpdateComponent.h"
#include "WorldState.h"

void PlayerUpdateComponent::update(float fps)
{
    if(sf::Joystick::isConnected(0))
    {
        m_TC->getLocation().x += ((m_Speed / 100) * m_XExtent) * fps;
        m_TC->getLocation().y += ((m_Speed / 100) * m_YExtent) * fps;
    }
    if(m_IsHoldingLeft)
    {
        m_TC->moveLeft(fps);
        
    }
    else if(m_IsHoldingRight)
    {
        m_TC->moveRight(fps);

    }
    if(m_IsHoldingUp)
    {
        m_TC->moveUp(fps);
    }
    else if(m_IsHoldingDown)
    {
        m_TC->moveDown(fps);
    }
    m_RCC->setOrMoveCollider(m_TC->getLocation().x, m_TC->getLocation().y,
            m_TC->getSize().x, m_TC->getSize().y);
    if(m_TC->getLocation().x > WorldState::WORLD_WIDTH - m_TC->getSize().x)
    {
        m_TC->getLocation().x = WorldState::WORLD_WIDTH - m_TC->getSize().x;
    }
    else if(m_TC->getLocation().x < 0)
    {
        m_TC->getLocation().x = 0;
    }
    if(m_TC->getLocation().y > WorldState::WORLD_HEIGHT - m_TC->getSize().y)
    {
        m_TC->getLocation().y = WorldState::WORLD_HEIGHT - m_TC->getSize().y;
    }
    else if(m_TC->getLocation().y < 0)
    {
        m_TC->getLocation().y = 0;
    }
    
    m_AGC->update(fps);
    
    //m_TC->decelerate(fps);
}
void PlayerUpdateComponent::updateShipTravelWithController(float x, float y)
{
    m_XExtent = x;
    m_YExtent = y;
}
void PlayerUpdateComponent::moveLeft()
{
    m_IsHoldingLeft = true;
    stopRight();
    stopUp();
    stopDown();
    //if (m_lastDirection != "left")
    {
        m_AGC->selectAnimation(0, 1, 7, 1);
    }
    m_lastDirection = "right";
}
void PlayerUpdateComponent::moveRight()
{
    m_IsHoldingRight = true;
    stopLeft();
    stopUp();
    stopDown();
	//if(m_lastDirection != "right")
	{
        m_AGC->selectAnimation(0, 0, 7, 0);
    }
    m_lastDirection = "right";
}
void PlayerUpdateComponent::moveUp()
{
    m_IsHoldingUp = true;
    stopDown();
    stopLeft();
    stopRight();
    m_lastDirection = "up";
}
void PlayerUpdateComponent::moveDown()
{
    m_IsHoldingDown = true;
    stopUp();
    stopLeft();
    stopRight();
    m_lastDirection = "down";
}
void PlayerUpdateComponent::stopLeft()
{
    m_IsHoldingLeft = false;
}
void PlayerUpdateComponent::stopRight()
{
    m_IsHoldingRight = false;
}
void PlayerUpdateComponent::stopUp()
{
    m_IsHoldingUp = false;
}
void PlayerUpdateComponent::stopDown()
{
    m_IsHoldingDown = false;
}