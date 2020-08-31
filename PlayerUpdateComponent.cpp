//
// Created by quatr on 23.04.2020.
//

#include "PlayerUpdateComponent.h"
#include "WorldState.h"

void PlayerUpdateComponent::update(float fps)
{
	//handle all player input and animations
    if(sf::Joystick::isConnected(0))
    {
        m_TC->getLocation().x += ((m_Speed / 100) * m_XExtent) * fps;
        m_TC->getLocation().y += ((m_Speed / 100) * m_YExtent) * fps;
    }
    if(m_SpaceClicked)
    {
		m_AGC->play("ATTACK", fps, true);
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
    //update player collider based on transform component
    m_RCC->setOrMoveCollider(m_TC->getLocation().x, m_TC->getLocation().y,
            m_TC->getSize().x, m_TC->getSize().y);
	//handle idle animation
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
    if (m_AGC->isDone("ATTACK"))
    {
        m_SpaceClicked = false;
    }
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

void PlayerUpdateComponent::attack()
{
    m_SpaceClicked = true;
}

void PlayerUpdateComponent::stopAttack()
{
    m_SpaceClicked = false;
}
