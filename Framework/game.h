#ifndef _main_game
#define _main_game
#include<stack>
#include<vector>
#include<SFML/Graphics.hpp>
#include"Util/txr_lookup.h"
#include"Util/no_copy.h"
#include"State/state_base.h"
constexpr auto SCREEN_WIDTH		= 1280;
constexpr auto SCREEN_HEIGHT	= 720;
constexpr auto X_TILES			= 14;
constexpr auto Y_TILES			= 8;
constexpr auto TILE_SIZE		= SCREEN_HEIGHT / Y_TILES;
class Game : public no_copy
{
private:
	sf::Clock								m_dt_clock;
	sf::RenderWindow						m_window;
	std::stack<std::unique_ptr<state_base>> m_states;
	bool									m_pop_pending = false;
	bool									m_swap_pending = false;
	std::unique_ptr<state_base>				m_swap_state;//hold state for swapping
	txr_lookup								m_txr_set;//hold information about obstacle texture
	
	state_base& cur_state() const;
	void pop();
	void swap();
	sf::Time update_dt_clock();
public:
	Game();
	//no_move
	Game(Game&&) = delete;
	void run();

	void pushState(std::unique_ptr<state_base>);
	
	//trigger bool var for pending pop/swap, prevent pop/swap too soon
	void popState();
	void swapState(std::unique_ptr<state_base> new_state);

	size_t getStateSize() const;
	const sf::RenderWindow& get_window() const;
	const txr_lookup& get_txr_set() const;
};
#endif // !_main_game

