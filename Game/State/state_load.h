#ifndef _state_load_h
#define _state_load_h
#include "../../PCH.h"
#include"../SaveLevel.h"
/*
case1
menu->load(m_change=stateplaying)
menu->load<->m_change
menu->stateplaying
case2
menu->stateplaying->load
menu->stateplaying->load(m_change=stateplaying)
menu->stateplaying->(popped)
menu->stateplaying<->m_change
menu->NEW_stateplaying
*/
const std::string warning = "LOAD FAILED";
class state_load :public state_base {
private:
	StackMenu				load_menu;
	std::string             name;
	SaveInf                 load_inf;
	bool					is_fail = false;
	Widget::Text            fail_label;
	sf::RectangleShape      background;
	sf::RectangleShape		background2;
public:
	state_load(Game&);

	void handleEvent(sf::Event e)			override;
	void update(sf::Time delta_time)		override;
	void draw(sf::RenderTarget& renderer)	override;
};
#endif // !_state_load_h