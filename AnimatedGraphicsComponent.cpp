#include "AnimatedGraphicsComponent.h"
#include "BitmapStore.h"

void AnimatedGraphicsComponent::update(float dt)
{
	//timer update
	timer += 10.f * dt;
	std::cout << timer << std::endl;
	
	if(timer >= animationTimer)
	{
		//reset timer
		timer = 0.f;
		//animate
		std::cout << "dziala" << std::endl;
		if(m_CurrRect != m_EndRect)
		{
			m_CurrRect.left += width;
		}
		//reset
		else
		{
			m_CurrRect.left = m_StartRect.left;
		}
		m_Sprite.setTextureRect(m_CurrRect);
	}
}

void AnimatedGraphicsComponent::selectAnimation(int x_frame_s, int y_frame_s, int x_frame_e, int y_frame_e)
{
	m_StartRect = sf::IntRect(x_frame_s * width, y_frame_s * height, width, height);
	m_CurrRect = m_StartRect;
	m_EndRect = sf::IntRect(x_frame_e * width, y_frame_e * height, width, height);
}

void AnimatedGraphicsComponent::draw(sf::RenderWindow& window, std::shared_ptr<TransformComponent> t)
{
	m_Sprite.setPosition(t->getLocation());
	window.draw(m_Sprite);
}

void AnimatedGraphicsComponent::initializeGraphics(std::string bitmapName, sf::Vector2f objectSize)
{
	BitmapStore::addBitmap("graphics/" + bitmapName + ".png");
	m_sheetTexture =  BitmapStore::getBitmap("graphics/" + bitmapName + ".png");
	m_Sprite.setTexture(m_sheetTexture, true);
	m_Sprite.setScale(float(objectSize.x) / (864/2), float(objectSize.y) / 140);
	m_StartRect = sf::IntRect(start_frame_x * width, start_row * height, width, height);
	m_EndRect = sf::IntRect(end_frame_x * width, end_row * height, width, height);
	m_Sprite.setTextureRect(m_StartRect);
	m_CurrRect = m_StartRect;
	
}
