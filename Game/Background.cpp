#include "Background.h"
Background::Background(const sf::Texture& texture, sf::Vector2f texture_size, sf::Vector2u num_frames, sf::Time delay)
	: m_animation((size_t)texture_size.x, (size_t)texture_size.y)
{
	m_sprite.setTexture(&texture);
	for (size_t i = 0; i < num_frames.y; ++i) {
		for (size_t j = 0; j < num_frames.x; ++j) {
			m_animation.add_frame(delay, i, j);
		}
	}
}

void Background::draw(sf::RenderTarget& render)
{
	sf::IntRect frame = m_animation.nextFrame();
	m_sprite.setTextureRect(frame);
	render.draw(m_sprite);
}

