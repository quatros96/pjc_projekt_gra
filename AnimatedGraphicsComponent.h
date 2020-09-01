#pragma once
#include "GraphicsComponent.h"
#include "GameObject.h"

class AnimatedGraphicsComponent : public GraphicsComponent
{
private:
	class Animation
	{
	public:
		//variables
        sf::Texture m_animationTexture;
        sf::Sprite m_animationSprite;
        float m_animationTimer = 1.f;
        float m_timer = 0.f;
        bool done = false;
        sf::IntRect m_StartRect;
        sf::IntRect m_CurrRect;
        sf::IntRect m_EndRect;
		//size of rect
        int m_width = 108;
        int m_height = 140;
		//functions
		Animation(sf::Sprite& sprite, sf::Texture& texture, float animationTimer, int start_x, int start_y, int end_x, int end_y, int width, int height);
        const bool& play(float dt);
        const bool& play(float dt, float percentage);
        const bool& isDone();
        void pause();
        void reset();
	};
    std::map<std::string, std::shared_ptr<Animation>> animations;
    std::shared_ptr<std::vector<std::string>> m_AnimationsInStrings;
    std::shared_ptr<Animation> priorityAnimation = nullptr;
    sf::Texture m_textureSheet;
    sf::Sprite m_Sprite;
    sf::Sprite m_currAnimationSprite;
    std::string m_SpecificType = "animated";
    std::shared_ptr<Animation> lastAnimation = nullptr;
    void addAnimationsFromStrings();
public:
    AnimatedGraphicsComponent() = default;
    void addAnimation(std::string key, float animationTimer, int start_frame_x, int start_frame_y, int frame_x, int frame_y, int width, int height);
    void play(std::string key, float& dt, bool priority = false);
    void play(std::string key, float& dt, float modifier, float modifier_max, bool priority = false);
    const bool& isDone(std::string key);
	
    void draw(sf::RenderWindow& window, std::shared_ptr<TransformComponent> t);
    void initializeGraphics(std::string bitmapName, sf::Vector2f objectSize);
    std::string getSpecificType()
    {
        return m_SpecificType;
    }
    void start(GameObjectSharer* gos, GameObject* self) override
    {
        m_AnimationsInStrings = self->getObjectAnimations();
        addAnimationsFromStrings();
    }
};

