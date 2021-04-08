#ifndef _World_h
#define _World_h
#include"../PCH.h"
#include"Entity/Player.h"
#include"Entity/Road.h"
#include "SaveLevel.h"

//function for init new vehicle
using lane_ptr = std::function < std::unique_ptr<Lane>(const sf::Vector2f road_pos, const Lane::direction dir, float speed) >;

class World {
private:
	std::vector<std::unique_ptr<Lane>> m_lanes;
	Player					m_player;
	TileMap					m_background;
	bool					m_game_over = false;
	int						m_best_lane;//the highest lane player walked on in a level (the lowest y pos)
	const txr_lookup&			m_txr_inf;//collection of texture infos use for obstacle

	std::vector<std::pair<std::string, std::string>> horn_set;
	sf::Sound m_horn;
	float m_honk_time = mtrand::getFloat(0.5f, 10.f);
	sf::Clock m_honk_clock;
public:
	World(const txr_lookup&, int cur_best_lane = Y_TILES - 1);
	void initLane(const SaveInf&);
	void resetWorld(const SaveInf&);
	void draw(sf::RenderTarget& target);
	void input();
	void update(float dt);
	bool tryPlayerCollideWith();
	bool updateScore();
	unsigned updateLevel();
	bool is_game_over() const;
	sf::Vector2f getPosition() const;
	int     get_max_lane() const;
};
#endif // !_World_h
