#ifndef _animation_h
#define _animation_h
#include<SFML/Graphics.hpp>
#include<vector>
class animation {
public:
	animation(size_t frame_width, size_t frame_height);
	void add_frame(sf::Time delay, size_t row, size_t col = 0);
	const sf::IntRect nextFrame();
	void	reset();
	const sf::IntRect getFrame(size_t) const;
	size_t	totalFrame() const;
private:
	struct frame {
		sf::Vector2i	pos;	//The position of the frame in a texture
		sf::Time		delay;  //Time delay to next frame
		frame(const sf::Vector2i pos, sf::Time delay);
		frame(int x, int y, sf::Time delay);
	};
	sf::Clock			m_timer;		//For progressing the animation
	std::vector<frame>	m_frames;		//List of animation frames
	size_t				m_frame_idx = 0;//The index of the current active frame
	const sf::Vector2i	m_frame_size;
};
#endif // !_animation_h
