#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f pos)
	: Collision()
{
	m_sprite.setPosition(pos);
}

Obstacle::Obstacle(sf::Vector2f pos, const sf::Texture& texture)
	: Collision((float)texture.getSize().x, (float)texture.getSize().y)
	, m_sprite(sf::Vector2f((float)texture.getSize().x, (float)texture.getSize().y))
{
	m_sprite.setPosition(pos);
	setTexture(texture);
}

Obstacle::Obstacle(sf::Vector2f pos , const sf::Texture& texture, sf::IntRect textureBound)
	: Collision((float)textureBound.width, (float)textureBound.height)
	, m_sprite(sf::Vector2f((float)textureBound.width, (float)textureBound.height))
{
	m_sprite.setPosition(pos);
	setTexture(texture, textureBound);
}

void Obstacle::setTexture(const sf::Texture& texture, const sf::IntRect& bounds)
{
	m_sprite.setTexture(&texture);
	m_sprite.setTextureRect(bounds);
	Collision::setSize((float)bounds.width, (float)bounds.height);
}

void Obstacle::setTexture(const sf::Texture& texture, bool resetRect)
{
	m_sprite.setTexture(&texture, resetRect);
	Collision::setSize((float)texture.getSize().x, (float)texture.getSize().y);
}

void Obstacle::setTextureRec(const sf::IntRect& bounds)
{
	m_sprite.setTextureRect(bounds);
}

void Obstacle::setSize(const sf::Vector2f& size)
{
	m_sprite.setSize(size);
	Collision::setSize(size);
}

//scale texture and collision size
void Obstacle::setScale(const sf::Vector2f& scale)
{
	m_sprite.setScale(scale);
	//set Collision size to match Sprite size
	const auto& spriteSize = m_sprite.getSize();
	const auto& spriteScale = m_sprite.getScale();
	Collision::setSize({ spriteSize.x * spriteScale.x,spriteSize.y * spriteScale.y });
}

void Obstacle::setPos(sf::Vector2f position)
{
	this->m_sprite.setPosition(position);
}

void Obstacle::draw(sf::RenderTarget& render) const
{
	render.draw(m_sprite);
}

void Obstacle::move(float speed)
{
	m_sprite.move(speed, 0);
}

const sf::Vector2f& Obstacle::getPosition() const
{
	return m_sprite.getPosition();
}

const sf::Vector2f& Obstacle::getSize() const
{
	return m_sprite.getSize();
}


Car::Car(sf::Vector2f pos, const sf::Texture& texture)
	: Obstacle(pos, texture)
{}

Car::Car(sf::Vector2f pos, const sf::Texture& texture, sf::IntRect textureBound)
	: Obstacle(pos, texture, textureBound)
{}
Truck::Truck(sf::Vector2f pos, const sf::Texture& texture)
	: Obstacle(pos, texture)
{}

Truck::Truck(sf::Vector2f pos, const sf::Texture& texture, sf::IntRect textureBound)
	: Obstacle(pos, texture, textureBound)
{}

Bird::Bird(sf::Vector2f pos, const sf::Texture& texture)
	: Obstacle(pos, texture)
{}

Bird::Bird(sf::Vector2f pos, const sf::Texture& texture, sf::IntRect textureBound)
	: Obstacle(pos, texture, textureBound)
{}

Dino::Dino(sf::Vector2f pos, const sf::Texture& texture)
	: Obstacle(pos, texture)
{}

Dino::Dino(sf::Vector2f pos, const sf::Texture& texture, sf::IntRect textureBound)
	: Obstacle(pos, texture, textureBound)
{}
