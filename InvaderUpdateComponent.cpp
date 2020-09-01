
#include "InvaderUpdateComponent.h"
#include "BulletSpawner.h"
#include "WorldState.h"
#include "SoundEngine.h"

void InvaderUpdateComponent::update(float fps)
{
	m_AttackTimer += 10.f * fps;
	if(abs(m_PlayerRCC->getPosition().x - m_RCC->getPosition().x) < 100 && abs(m_PlayerRCC->getPosition().y - m_RCC->getPosition().y) < 100)
	{
		chasePlayer(fps);
	}
	else
	{
		m_Timer += 4.f * fps;
		if(m_Timer > 10)
		{
			goLeft = !goLeft;
			m_Timer = 0;
		}
		if(goLeft)
		{
			m_TC->moveLeft(fps);
			m_AGC->play("LEFT", fps);
		}
		else
		{
			m_TC->moveRight(fps);
			m_AGC->play("RIGHT", fps);
		}
	}
	if(m_AttackTimer > 10)
	{
		isAbleToAttack = true;
		m_AttackTimer = 0;
	}
	m_RCC->setOrMoveCollider(m_TC->getLocation().x, m_TC->getLocation().y,
		m_TC->getSize().x, m_TC->getSize().y);
}

void InvaderUpdateComponent::chasePlayer(float& fps)
{
	if(m_RCC->getWorldGridPosition().x > m_PlayerRCC->getWorldGridPosition().x)
	{
		//go left
		m_TC->moveLeft(fps);
		m_AGC->play("LEFT", fps);
	}
	else if (m_RCC->getWorldGridPosition().x < m_PlayerRCC->getWorldGridPosition().x)
	{
		//go right
		m_TC->moveRight(fps);
		m_AGC->play("RIGHT", fps);
	}
	else if(m_RCC->getWorldGridPosition().y > m_PlayerRCC->getWorldGridPosition().y)
	{
		//go up
		m_TC->moveUp(fps);
		m_AGC->play("UP", fps);
	}
	else if (m_RCC->getWorldGridPosition().y < m_PlayerRCC->getWorldGridPosition().y)
	{
		//go down
		m_TC->moveDown(fps);
		m_AGC->play("DOWN", fps);
	}
}

void InvaderUpdateComponent::Attack()
{
	isAbleToAttack = false;
}

bool InvaderUpdateComponent::canAttack()
{
	return isAbleToAttack;
}

void InvaderUpdateComponent::initializeBulletSpawner(BulletSpawner *bulletSpawner, int randSeed)
{
    m_BulletSpawner = bulletSpawner;
    m_RandSpeed = randSeed;
    srand(m_RandSpeed);
    m_TimeBetweenShots = (rand() % 15 + m_RandSpeed);

}
