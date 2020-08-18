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
        m_AGC->play("LEFT", fps);
    }
    else if(m_IsHoldingRight)
    {
        m_TC->moveRight(fps);
        m_AGC->play("RIGHT", fps);
    }
    if(m_IsHoldingUp)
    {
        m_TC->moveUp(fps);
        m_AGC->play("UP", fps);
    }
    else if(m_IsHoldingDown)
    {
        m_TC->moveDown(fps);
        m_AGC->play("DOWN", fps);
    }
    m_RCC->setOrMoveCollider(m_TC->getLocation().x, m_TC->getLocation().y,
            m_TC->getSize().x, m_TC->getSize().y);
	//EDGES OF WORLD COLLISIONS
    if(m_RCC->getPosition().x > WorldState::WORLD_WIDTH - m_RCC->getSize().x)
    {
        m_TC->getLocation().x = WorldState::WORLD_WIDTH - m_RCC->getSize().x - m_RCC->getOffsets().x;
    }
    else if(m_RCC->getPosition().x < 0)
    {
        m_TC->getLocation().x = -m_RCC->getOffsets().x;
    }
    if(m_TC->getLocation().y > WorldState::WORLD_HEIGHT - m_TC->getSize().y)
    {
        m_TC->getLocation().y = WorldState::WORLD_HEIGHT - m_RCC->getSize().y - m_RCC->getOffsets().y;
    }
    else if(m_TC->getLocation().y < 0)
    {
        m_TC->getLocation().y = -m_RCC->getOffsets().y;
    }
	//END OF EDGES OF WORLD COLLISIONS
    if(!m_IsHoldingLeft && !m_IsHoldingRight && !m_IsHoldingUp && !m_IsHoldingDown)
    {
	    if(m_lastDirection == "left")
	    {
            m_AGC->play("IDLE_LEFT", fps);
	    }
        else if (m_lastDirection == "right")
        {
            m_AGC->play("IDLE_RIGHT", fps);
        }
        else if (m_lastDirection == "up")
        {
            m_AGC->play("IDLE_UP", fps);
        }
        else
        {
            m_AGC->play("IDLE_DOWN", fps);
        }
    }
    
    
    
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
    m_lastDirection = "left";
}
void PlayerUpdateComponent::moveRight()
{
    m_IsHoldingRight = true;
    stopLeft();
    stopUp();
    stopDown();
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