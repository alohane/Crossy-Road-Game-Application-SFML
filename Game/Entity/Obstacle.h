#ifndef Vehicle_h
#define Vehicle_h

#include "../../PCH.h"
#include "../Collidable.h"


class Obstacle : public Collision {
private:
	sf::RectangleShape m_sprite;
public:
	Obstacle(sf::Vector2f pos);
	Obstacle(sf::Vector2f pos, const sf::Texture&);
	Obstacle(sf::Vector2f pos, const sf::Texture&, sf::IntRect textureBound);

	void setTexture(const sf::Texture&, const sf::IntRect&);
	void setTexture(const sf::Texture&, bool resetRect = false);
	void setTextureRec(const sf::IntRect&);
	void setPos(sf::Vector2f position);
	void setSize(const sf::Vector2f&);
	void setScale(const sf::Vector2f&);
	void move(float speed);
	const sf::Vector2f& getPosition()	const;
	const sf::Vector2f& getSize()		const;
	void draw(sf::RenderTarget&)		const;
};
class Car :public Obstacle {
public:
	Car(sf::Vector2f pos, const sf::Texture&);
	Car(sf::Vector2f pos, const sf::Texture&, sf::IntRect textureBound);
};
class Truck :public Obstacle {
public:
	Truck(sf::Vector2f pos, const sf::Texture&);
	Truck(sf::Vector2f pos, const sf::Texture&, sf::IntRect textureBound);
};
class Bird :public Obstacle {
public:
	Bird(sf::Vector2f pos, const sf::Texture&);
	Bird(sf::Vector2f pos, const sf::Texture&, sf::IntRect textureBound);
};
class Dino :public Obstacle {
public:
	Dino(sf::Vector2f pos, const sf::Texture&);
	Dino(sf::Vector2f pos, const sf::Texture&, sf::IntRect textureBound);
};

template<typename T>
std::unique_ptr<Obstacle> new_obstacle(sf::Vector2f pos, const sf::Texture& texture, sf::IntRect textureBound)
{
	return std::make_unique<T>(pos, texture, textureBound);
}
#endif // !Vehicle_h
	

