
#include "StandardGraphicsComponent.h"
#include "BitmapStore.h"
#include <iostream>

void StandardGraphicsComponent::initializeGraphics(std::string bitmapName, sf::Vector2f objectSize)
{
    BitmapStore::addBitmap("graphics/" + bitmapName + ".png");
    m_Sprite.setTexture(BitmapStore::getBitmap("graphics/" + bitmapName + ".png"));
    auto textureSize = m_Sprite.getTexture()->getSize();
    m_Sprite.setScale(float(objectSize.x) / textureSize.x, float(objectSize.y)/ textureSize.y);
    //m_Sprite.setColor(sf::Color(0, 255, 0));
}
void StandardGraphicsComponent::draw(sf::RenderWindow &window, std::shared_ptr<TransformComponent> t)
{
    m_Sprite.setPosition(t->getLocation());
    window.draw(m_Sprite);
}
void StandardGraphicsComponent::setRotation(float angle)
{
    m_Sprite.setRotation(angle);
}

int StandardGraphicsComponent::getRotation()
{
    return m_Sprite.getRotation();
}
