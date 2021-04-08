#include"playlist.h"

sf::Music& playlist::data()
{
	return m_track;
}

void playlist::play()
{

}

void playlist::add(const std::string& file_name)
{
	m_queue.push_back(file_name);
}

void playlist::remove(const std::string& file_name)
{
	m_queue.erase(std::find(m_queue.begin(), m_queue.end(), file_name));
}

void playlist::set_loop(bool repeat)
{
	m_repeat = repeat;
}

bool playlist::is_loop() const
{
	return m_repeat;
}

std::string playlist::cur_track_name() const
{
	return m_queue[m_cur_track];
}

size_t playlist::size() const
{
	return m_queue.size();
}
