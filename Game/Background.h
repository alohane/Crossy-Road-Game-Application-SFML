#include"../PCH.h"
class Background {
private:
	sf::RectangleShape	m_sprite = sf::RectangleShape({ SCREEN_WIDTH, SCREEN_HEIGHT });
	animation			m_animation;
public:
	Background(const sf::Texture&, sf::Vector2f texture_size, sf::Vector2u num_frames
		, sf::Time delay = sf::seconds(0.1f));
	void draw(sf::RenderTarget&);
};