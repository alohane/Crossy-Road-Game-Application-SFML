#ifndef _state_playing
#define _state_playing

#include "../../PCH.h"
#include "../World.h"
#include "state_pause.h"
#include "state_game_over.h"

class state_playing :public state_base {
private:
	SaveInf		m_save;
	World		m_world;
	sf::Music	m_ambient;
	sf::Music	m_music;
	unsigned	m_level			= 1;
	unsigned	m_score			= 0;
	bool		m_is_gameover	= false;
	PauseMenu	m_pause_menu;
	GameOver	m_gameover;
	class display {
	private:
		Widget::Text label;
		std::string  text;
		int currentdata;
		float centrepoint;
		void updateDisplay();
	public:
		display() = default;
		display(float centreY, const std::string& text);
		void update(int newdata);
		void draw(sf::RenderTarget& target);
	}m_score_display, m_level_display;
public:
	state_playing(Game&);//start at level 1
	state_playing(Game&, const SaveInf&);//call in state_load
	void handleEvent(sf::Event e)				override;
	void handleInput()							override;
	void update(sf::Time delta_time)			override;	
	void draw(sf::RenderTarget& renderer)		override;
	void initAmbient();//call on every constructor
	void pauseAllSound();
	void resumeAllSound();
	
	std::vector<SaveInf::LaneInf> randomSaveInf(unsigned lv);
};
#endif // !_state_playing/
