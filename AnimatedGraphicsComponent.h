#pragma once
#include "GraphicsComponent.h"

class Component;

class AnimatedGraphicsComponent : public GraphicsComponent
{
private:
    sf::Sprite m_Sprite;
    sf::Texture m_sheetTexture;
    float animationTimer = 1.f;
    int framesInRow = 7;
    int rows = 1;
    int start_frame_x = 0;
    int start_row = 0;
    int end_frame_x = 7;
    int end_row = 0;
    int width = 108;
    int height = 140;
    float timer = 0.f;
    sf::IntRect m_StartRect;
    sf::IntRect m_CurrRect;
    sf::IntRect m_EndRect;
    std::string m_SpecificType = "animated";
public:
    void update(float dt);
    void selectAnimation(int x_frame_s, int y_frame_s, int x_frame_e, int y_frame_e);
    void pauseAnimation();

    void resetAnimation()
    {
        timer = 0.f;
        m_CurrRect = m_StartRect;
    }

    void draw(sf::RenderWindow& window, std::shared_ptr<TransformComponent> t);
    void initializeGraphics(std::string bitmapName, sf::Vector2f objectSize);
    std::string getSpecificType()
    {
        return m_SpecificType;
    }
    void start(GameObjectSharer* gos, GameObject* self)
    {

    }
};

