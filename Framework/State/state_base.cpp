#include "state_base.h"

state_base::state_base(Game& Game)
	: m_game(Game)
{}

bool initMusic(sf::Music& music, const std::string& dir, float volume, bool loop)
{
	if (!music.openFromFile(dir))
		return false;
	music.setVolume(volume);
	music.setLoop(loop);
	music.play();
	return true;
}