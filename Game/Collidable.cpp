#include "Collidable.h"

Collision::Collision(const sf::Vector2f& size)
    : m_size(size)
{}

Collision::Collision(float width, float height)
    : m_size(width, height)
{}

bool Collision::tryCollideWith(Collision& other)
{
    if (getBox(20).intersects(other.getBox(0))) {
        onCollide(other);
        other.onCollide(*this);
        return true;
    }
    return false;
}

void Collision::setSize(sf::Vector2f new_size)
{
    m_size = new_size;
}

void Collision::setSize(float width, float height)
{
    m_size = { width,height };
}

void Collision::onCollide(Collision& other)
{}

sf::FloatRect Collision::getBox(int delta_X) const
{
    return
    {
        getPosition().x + delta_X,
        getPosition().y + delta_X,
        m_size.x,
        m_size.y
    };
}

