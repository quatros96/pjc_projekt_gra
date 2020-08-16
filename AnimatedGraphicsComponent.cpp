#include "AnimatedGraphicsComponent.h"
#include "BitmapStore.h"

AnimatedGraphicsComponent::Animation::Animation(sf::Sprite& sprite, sf::Texture& texture, float animationTimer,int start_frame_x, int start_frame_y, int frame_x, int frame_y, int width, int height):
	m_animationSprite(sprite), m_animationTexture(texture), m_animationTimer(animationTimer), m_width(width), m_height(height)
{
	m_StartRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
	m_EndRect = sf::IntRect(frame_x * width, frame_y * height, width, height);
	m_CurrRect = m_StartRect;
	m_animationSprite.setTexture(m_animationTexture, true);
	m_animationSprite.setTextureRect(m_StartRect);
}

void AnimatedGraphicsComponent::Animation::play(float dt)
{
	//timer update
	m_timer += 1000.f * dt;
	if(m_timer >= m_animationTimer)
	{
		m_timer = 0.f;
		if (m_CurrRect != m_EndRect)
		{
			m_CurrRect.left += m_width;
		}
		//reset
		else
		{
			m_CurrRect.left = m_StartRect.left;
		}
		m_animationSprite.setTextureRect(m_CurrRect);
	}
}

void AnimatedGraphicsComponent::Animation::reset()
{
	m_timer = 0.f;
	m_CurrRect = m_StartRect;
}

void AnimatedGraphicsComponent::addAnimation(std::string key, float animationTimer, int start_frame_x, int start_frame_y, int frame_x, int frame_y, int width, int height)
{
	animations[key] = std::make_shared<Animation>(m_Sprite, m_textureSheet, animationTimer, start_frame_x, start_frame_y, frame_x, frame_y, width, height);
}

void AnimatedGraphicsComponent::play(std::string key, float& dt)
{
	if(lastAnimation != animations[key])
	{
		if(lastAnimation == nullptr)
		{
			lastAnimation = animations[key];
		}
		else
		{
			lastAnimation->reset();
			lastAnimation = animations[key];
		}
	}
	m_currAnimationSprite = animations[key]->m_animationSprite;
	animations[key]->play(dt);
}


void AnimatedGraphicsComponent::draw(sf::RenderWindow& window, std::shared_ptr<TransformComponent> t)
{
	/*
		for(auto animation : animations)
	{
		animation.second->m_animationSprite.setPosition(t->getLocation());
		window.draw(animation.second->m_animationSprite);
	}
	 */
	m_currAnimationSprite.setPosition(t->getLocation());
	window.draw(m_currAnimationSprite);
	
}

void AnimatedGraphicsComponent::initializeGraphics(std::string bitmapName, sf::Vector2f objectSize)
{
	BitmapStore::addBitmap("graphics/" + bitmapName + ".png");
	m_textureSheet =  BitmapStore::getBitmap("graphics/" + bitmapName + ".png");
	m_Sprite.setTexture(m_textureSheet, true);
	m_Sprite.setScale(float(objectSize.x) / 16, float(objectSize.y) / 9);
	//addAnimation("RUNL", 100.f, 0, 0, 7, 0, 108, 140);
	//addAnimation("RUNR", 100.f, 0, 1, 7, 1, 108, 140);
	addAnimation("UP", 100.f, 1, 8, 8, 8, 64, 64);
	addAnimation("LEFT", 100.f, 1, 9, 8, 9, 64, 64);
	addAnimation("DOWN", 100.f, 1, 10, 8, 10, 64, 64);
	addAnimation("RIGHT", 100.f, 1, 11, 8, 11, 64, 64);
	addAnimation("IDLE_UP", 100.f, 0, 8, 0, 8, 64, 64);
	addAnimation("IDLE_LEFT", 100.f, 0, 9, 0, 9, 64, 64);
	addAnimation("IDLE_DOWN", 100.f, 0, 10, 0, 10, 64, 64);
	addAnimation("IDLE_RIGHT", 100.f, 0, 11, 0, 11, 64, 64);
}
