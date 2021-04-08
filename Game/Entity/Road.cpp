#include "Road.h"


Lane::Lane(const sf::Vector2f road_pos, const direction dir, float speed)
	: m_vehicle_pos(road_pos)
	, m_dir(dir)
	, m_speed(speed)
	, m_vehicles_texture(nullptr)	
{}

void Lane::initObstacle(size_t size)
{
	if (size >= 5)
		size = 5;//max vehicle
	m_num_vehicle = size;//init max vehicle

	if (m_init_func) {
		if (m_dir == direction::right) {
			float spacing = SCREEN_WIDTH / (float)size;
			//float x = LEFT_BOUND + (float)mtrand::getDouble(320-spacing, 320);
			float x = LEFT_BOUND+(float)mtrand::getDouble(0,150);
			size += HIDDEN_VEHICLE;//increase size with extra vehicle

			m_vehicles.reserve(size);
			for (size_t i = 0; i < size; ++i) {
				x += spacing;
				//create vehicle at x, lanePos.y
				auto new_obstacle = m_init_func(sf::Vector2f(x, m_vehicle_pos.y), *m_vehicles_texture, m_texture_bound);
				float scale = OBSTACLE_SIZE / m_texture_bound.height;
				new_obstacle->setScale(sf::Vector2f(scale, scale));

				m_vehicles.push_back(std::move(new_obstacle));
			}
		}
		else {
			float spacing = SCREEN_WIDTH / (float)size;
			float x = SCREEN_WIDTH - LEFT_BOUND- (float)mtrand::getDouble(0, 150);

			size += HIDDEN_VEHICLE;//increase size with extra vehicle

			m_vehicles.reserve(size);
			for (size_t i = 0; i < size; ++i) {
				x -= spacing;
				//create vehicle at x, lanePos.y
				auto new_obstacle = m_init_func(sf::Vector2f(x, m_vehicle_pos.y), *m_vehicles_texture, m_texture_bound);
				float scale = OBSTACLE_SIZE / m_texture_bound.height;
				new_obstacle->setScale(sf::Vector2f(scale, scale));

				m_vehicles.push_back(std::move(new_obstacle));
			}
		}
	}
}

void Lane::setType(obstacle_ptr funct, sf::Texture& vehicle, sf::IntRect texture_bound)
{
	m_init_func = funct;
	m_vehicles_texture = &vehicle;
	m_texture_bound = texture_bound;
}

size_t Lane::getVehicleSize() const
{
	return m_vehicles.size();
}

Obstacle& Lane::getVehicle(size_t idx)
{
	return *m_vehicles[idx];
}

void Lane::update(float dt)
{
	float speed = m_speed * (int)m_dir * dt;//set speed for vehicle

	float spacing = SCREEN_WIDTH / (float)(m_num_vehicle);//space between 2 car

	for (size_t i = 0; i < this->m_vehicles.size(); i++)
	{
		this->m_vehicles[i]->move(2.f * speed);
		if (this->m_dir == direction::left && this->m_vehicles[i]->getPosition().x + OBSTACLE_SIZE >= SCREEN_WIDTH + spacing) {
			this->m_vehicles[i]->setPos({ BASE_X - OBSTACLE_SIZE, m_vehicle_pos.y });
		}
		if (this->m_dir == direction::right && (this->m_vehicles[i]->getPosition().x) <= -spacing) {
			this->m_vehicles[i]->setPos({ SCREEN_WIDTH, m_vehicle_pos.y });
		}
	}
}

void Lane::draw(sf::RenderTarget& target)
{
	for (auto& e : this->m_vehicles) {
		e->draw(target);
	}
}

void Lane::pause(bool setPause)
{
	is_paused = setPause;
}

bool Lane::isPause()const
{
	return is_paused;
}

D_Lane::D_Lane(const sf::Vector2f road_pos, const direction dir, float speed)
	: Lane(road_pos,dir,speed),
	m_light(road_pos) 
{}

void D_Lane::update(float dt)
{	
	if (m_light.getLightState() == (sf::Color::Green)) {
		if (m_clock.getElapsedTime() <= (m_start_time_change_color + m_green_time)/*time green light*/) {
			Lane::update(dt);
		}
		else {
			m_light.turnRed();//turn red light
			float red_time = 0.5f + mtrand::getFloat(0,1);
			m_red_time = sf::seconds(red_time);
			m_start_time_change_color = m_clock.getElapsedTime();
		}
	}
	else {
		if (m_clock.getElapsedTime() >= (m_start_time_change_color + m_red_time)) {
			m_light.turnGreen();
			float green_time = 5.f + mtrand::getFloat(0, 2);
			m_start_time_change_color = m_clock.getElapsedTime();
			m_green_time = sf::seconds(green_time);
		}
	}
}

void D_Lane::draw(sf::RenderTarget& target)
{
	m_light.draw(target);//draw traffic light
	Lane::draw(target);
}

A_Lane::A_Lane(const sf::Vector2f road_pos, const direction dir, float speed)
	: Lane(road_pos, dir, speed)
{}

void A_Lane::update(float dt)
{
	Lane::update(dt);
}

void A_Lane::draw(sf::RenderTarget& target)
{
	Lane::draw(target);
}