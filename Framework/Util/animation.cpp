#include "animation.h"

animation::frame::frame(const sf::Vector2i pos, sf::Time delay)
	: pos(pos)
	, delay(delay)
{}

animation::frame::frame(int x, int y, sf::Time delay)
	: pos(x,y)
	, delay(delay)
{}

animation::animation(size_t frame_width, size_t frame_height)
	: m_frame_size(frame_width, frame_height)
{}

void animation::add_frame(sf::Time delay, size_t row, size_t col)
{
	m_frames.emplace_back(col * m_frame_size.x, row * m_frame_size.y, delay);
}

const sf::IntRect animation::nextFrame()
{
	if (m_timer.getElapsedTime() >= m_frames[m_frame_idx].delay) {
		m_timer.restart();
		++m_frame_idx;//next frame idx
		if (m_frame_idx == m_frames.size())//loop back
			reset();
	}
	return sf::IntRect(m_frames[m_frame_idx].pos, m_frame_size);
}

const sf::IntRect animation::getFrame(size_t idx) const
{
	return sf::IntRect(m_frames[m_frame_idx].pos, m_frame_size);
}

void animation::reset()
{
	m_frame_idx = 0;
}

size_t animation::totalFrame() const
{
	return m_frames.size();
}
