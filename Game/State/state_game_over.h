#ifndef _STATE_GAME_OVER_H_
#define _STATE_GAME_OVER_H_
#include"../../PCH.h"
#include"../SaveLevel.h"
const	std::string Score_label ="SCORE";
const	std::string HighScore_label ="HIGH SCORE";
const	std::string NewHighScore_label = "\tNEW  HIGH  SCORE\n";

class GameOver {
private:
	Game&							 m_game;
	StackMenu				m_gameover_menu;
	bool			 new_high_score = false;
	bool					 m_exit = false;
	Widget::Text					  label;
	Widget::Text				    m_score;
	Widget::Text			    m_highscore;
	sf::RectangleShape			  container;

	int	score = 0;
	int highscore = 0;
public:
	GameOver(Game&)						;

	bool GetState()						;
	void draw(sf::RenderTarget& target)	;
	void handleEvent(sf::Event e)		;
	void update(sf::Time dt)			;
	void updateScore(int score)			;
};
#endif // !_STATE_GAME_OVER_H_
