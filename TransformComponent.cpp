//
// Created by quatr on 23.04.2020.
//

#include "TransformComponent.h"

TransformComponent::TransformComponent(float width, float height, sf::Vector2f location, float speed)
{
    m_Height = height;
    m_Width = width;
    m_Location = location;
    m_Speed = speed;
}

void TransformComponent::moveLeft(float dt)
{
    //m_CurrSpeed += m_Acceleration * dt;
    m_Location.x -= m_Speed * dt;
}

void TransformComponent::moveRight(float dt)
{
    m_Location.x += m_Speed * dt;
}

void TransformComponent::moveUp(float dt)
{
    m_Location.y -= m_Speed * dt;
}

void TransformComponent::moveDown(float dt)
{
    m_Location.y += m_Speed * dt;
}

sf::Vector2f& TransformComponent::getLocation()
{
    return m_Location;
}

void TransformComponent::setLocation(sf::Vector2f position)
{
    m_Location = position;
}

sf::Vector2f  TransformComponent::getSize()
{
    return sf::Vector2f (m_Width, m_Height);
}
