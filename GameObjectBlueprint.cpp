//
// Created by quatr on 27.04.2020.
//

#include "GameObjectBlueprint.h"

float GameObjectBlueprint::getSpeed()
{
    return m_Speed;
}

void GameObjectBlueprint::setSpeed(float speed)
{
    m_Speed = speed;
}

float GameObjectBlueprint::getWidth()
{
    return m_Width;
}
void GameObjectBlueprint::setWidth(float width)
{
    m_Width = width;
}
float GameObjectBlueprint::getHeight()
{
    return m_Height;
}
void GameObjectBlueprint::setHeight(float height)
{
    m_Height = height;
}
float GameObjectBlueprint::getLacationX()
{
    return m_LocationX;
}
void GameObjectBlueprint::setLocationX(float locationX)
{
    m_LocationX = locationX;
}
float GameObjectBlueprint::getLocationY()
{
    return m_LocationY;
}
void GameObjectBlueprint::setLocationY(float locationY)
{
    m_LocationY = locationY;
}
void GameObjectBlueprint::setName(std::string name)
{
    m_Name = "" + name;
}
std::string GameObjectBlueprint::getName()
{
    return m_Name;
}
std::vector<std::string>& GameObjectBlueprint::getComponentList()
{
    return m_ComponentList;
}
void GameObjectBlueprint::addToComponentList(std::string newComponent)
{
    m_ComponentList.push_back(newComponent);
}
std::string GameObjectBlueprint::getBitmapName()
{
    return m_BitmapName;
}
void GameObjectBlueprint::setBitmapName(std::string bitmapName)
{
    m_BitmapName = "" + bitmapName;
}
std::string GameObjectBlueprint::getEncompassingRectColliderLabel()
{
    return m_EncompassingRectColliderLabel;
}
bool GameObjectBlueprint::getEncompassingRectCollider()
{
    return m_EncompassingRectCollider;
}
void GameObjectBlueprint::setEncompassingRectCollider(std::string label)
{
    m_EncompassingRectCollider = true;
    m_EncompassingRectColliderLabel = "" + label;
}