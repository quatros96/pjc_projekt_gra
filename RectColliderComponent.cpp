//
// Created by quatr on 23.04.2020.
//

#include "RectColliderComponent.h"
#include "WorldState.h"

RectColliderComponent::RectColliderComponent(std::string name, float widthOffset, float heightOffset) 
{
    m_Tag = "" + name;
    m_Collider.setFillColor(sf::Color::Transparent);
    m_Collider.setOutlineColor(sf::Color::Red);
    m_Collider.setOutlineThickness(-1.f);
    m_WidthOffset = widthOffset;
    m_HeightOffset = heightOffset;
}
std::string RectColliderComponent::getColliderTag()
{
    return m_Tag;
}
void RectColliderComponent::setOrMoveCollider(float x, float y, float width, float height)
{
    m_Collider.setPosition(x + m_WidthOffset, y + m_HeightOffset);
    m_Collider.setSize(sf::Vector2f(width, height));
}
sf::RectangleShape& RectColliderComponent::getColliderRectF()
{
    return m_Collider;
}

void RectColliderComponent::draw(sf::RenderWindow& window)
{
	if(WorldState::DEBUG_MODE)
	{
        m_Collider.setOutlineThickness(-1.f);
	}
    else
    {
        m_Collider.setOutlineThickness(0);
    }
    window.draw(m_Collider);
}

sf::Vector2f RectColliderComponent::getPosition()
{
    return sf::Vector2f(m_Collider.getPosition().x, m_Collider.getPosition().y);
}

sf::Vector2f RectColliderComponent::getSize()
{
    return m_Collider.getSize();
}

sf::Vector2f RectColliderComponent::getOffsets()
{
    return sf::Vector2f(m_WidthOffset, m_HeightOffset);
}

void RectColliderComponent::setColliderRotation(int angle)
{
    m_Collider.setRotation(angle);
}

int RectColliderComponent::getColliderRotation()
{
    return m_Collider.getRotation();
}

sf::Vector2u RectColliderComponent::getWorldGridPosition()
{
    return sf::Vector2u(m_Collider.getPosition().x / WorldState::TILE_SIZE, m_Collider.getPosition().y / WorldState::TILE_SIZE);
}
