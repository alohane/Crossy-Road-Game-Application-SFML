#include "World.h"
#include<iostream>
World::World(const txr_lookup& lookup, int best_lane)
	: m_txr_inf(lookup)
	, m_background(&asset::texture().get("road_textures", "png"), sf::Vector2u(20, 20))//size base on the tileset.png
	, m_best_lane(best_lane)
{
	//render background map(top to bottom)
	const std::vector<unsigned> tile_map = { 1,0,1,0,1,0,1,0 };
	//render Y_TILES+1 to fill whole screen
	m_background.setMapSize(X_TILES+1, Y_TILES);
	////scale the texture to TILE_SIZE (90)
	//m_background.create_map(tile_map, sf::Vector2u(TILE_SIZE, TILE_SIZE));

	//TESTING HORN EFFECT
	horn_set.emplace_back("car_horn1", "ogg");
	horn_set.emplace_back("car_horn2", "ogg");
	//std::cout << m_honk_time << std::endl;
	int rand_sound = mtrand::getInt(0, horn_set.size() - 1);
	m_horn.setBuffer(asset::sound().get(horn_set[rand_sound].first, horn_set[rand_sound].second));
	m_horn.setVolume(5);
}

void World::initLane(const SaveInf& save)
{
	//function for init
	m_lanes.reserve(SAVE_LANE);
	//array for rendering background map
	std::vector<unsigned> tile_map(Y_TILES);
	obstacle_ptr initObstacleFunc[2][2] = { {new_obstacle<Truck> , new_obstacle<Car>},{new_obstacle<Bird> , new_obstacle<Dino>} };
	lane_ptr initLaneFunc[]		= { new_lane<D_Lane>,new_lane<A_Lane> };
	const std::string types[]	= { "vehicle" , "animal" };
	for (size_t i = 0; i < save.get_size(); ++i) {
		const auto&		laneInf = save.get_RoadInf(i);					//get each laneInf from save file
		float lanePos			= (float)laneInf.lanePos * TILE_SIZE;
		size_t type_idx			= laneInf.laneType;
		m_lanes.emplace_back(initLaneFunc[type_idx](sf::Vector2f(0, lanePos), (Lane::direction)laneInf.direction, laneInf.speed));

		const std::string& type = types[type_idx];
		/*use for set vInfo type and its texture*/
		const txr_set&	set		= m_txr_inf[type][laneInf.obstacleType];	//get a set of multiple texture of a vInfo type
		unsigned		idx		= mtrand::getInt(0, set.size() - 1);		//random to choose a texture for obstacle in that road
		const txr_inf&	vInfo	= set.getFullInf(idx);						//get all info about texture
		sf::Texture&		texture	= asset::texture().get(vInfo.name, vInfo.ext);
		const sf::IntRect	bounds	= (laneInf.direction == (int)Lane::direction::left) 
			? vInfo.getBounds(0) /*left texture*/
			: vInfo.getBounds(1);/*right texture*/

		/*set function for init, texture and texture bounds*/
		Lane& newLane = *m_lanes.back();
		newLane.setType(initObstacleFunc[type_idx][laneInf.obstacleType], texture, bounds);
		newLane.initObstacle(laneInf.obstacleNum);

		tile_map[laneInf.lanePos] = 1;
	}
	m_background.create_map(tile_map, sf::Vector2u(TILE_SIZE, TILE_SIZE));
}

void World::input()
{
	if (m_player.isAlive()) {
		m_player.input();
	}
}

bool World::is_game_over() const {
	return m_game_over;
}

void World::update(float dt)
{
	m_player.update();
	this->tryPlayerCollideWith();
	for (auto& lane : this->m_lanes)
		lane->update(dt);
	float test = m_honk_clock.getElapsedTime().asSeconds();
	if (test >= m_honk_time) {
		int rand_sound = mtrand::getInt(0, horn_set.size() - 1);
		m_horn.setBuffer(asset::sound().get(horn_set[rand_sound].first, horn_set[rand_sound].second));
		m_honk_time = mtrand::getFloat(3.f, 10.f);
		//std::cout << m_honk_time << std::endl;
		m_honk_clock.restart();
		m_horn.play();
	}
}

bool World::updateScore()
{
	int cur_lane = (int)(m_player.getPosition().y / TILE_SIZE);
	if (cur_lane < m_best_lane) {
		m_best_lane = cur_lane;
		return true;
	}
	return false;
}

unsigned World::updateLevel()
{
	unsigned level = 0;
	if (m_player.isPassLevel()) {
		level = 1;
	}
	return level;
}

void World::resetWorld(const SaveInf& new_save)
{
	m_lanes.clear();
	m_player.restart();
	m_best_lane = Y_TILES - 1;
	initLane(new_save);
}

void World::draw(sf::RenderTarget& target)
{
	target.draw(m_background);
	for (auto& lane : m_lanes) {
		lane->draw(target);
	}
	m_player.moving();
	m_player.animationRenderer();
	m_player.draw(target);
}

bool World::tryPlayerCollideWith() {
	for (size_t i = 0; i < m_lanes.size(); i++) {
		if (!m_player.isAlive())
			continue;
		for (int j = m_lanes[i]->getVehicleSize() - 1; j >= 0; j--) {
			if (m_player.tryCollideWith(m_lanes[i]->getVehicle(j))) {
				//std::cout << "Collided!\n";
				m_player.deathSoundPlaying();
				m_game_over = true;
				return true;
			}
		}
	}
	return false;
}

sf::Vector2f World::getPosition() const
{
	return m_player.getPosition();
}

int World::get_max_lane() const
{
	return m_best_lane;
}