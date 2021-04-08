#ifndef PAUSEMENU_H_
#define PAUSEMENU_H_

#include "../../PCH.h"
#include"../SaveLevel.h"
class PauseMenu {
private:
	StackMenu					m_menu;
	bool			m_isPaused = false;
	SaveInf						m_save;
public:
	PauseMenu(Game&)						;
	void changeState()						;
	bool isPaused()							;
	void draw(sf::RenderTarget& target)		;
	void handleEvent(sf::Event e,Game&)		;
	void update(sf::Time dental_time)		;
	void updateSaveInfo(SaveInf& save)      ;
};


#endif // !PAUSEMENU_H_