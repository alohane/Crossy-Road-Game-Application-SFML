#ifndef _road_h
#define _road_h
#include "../../PCH.h"
#include "Obstacle.h"
#include "TrafficLight.h"

constexpr auto MIN_VEHICLE = 3;
constexpr auto Y_DISTANCE_LIGHT_VS_LANE = 90.f;

using CollisionResult = std::pair<int, std::vector<sf::Vector2f>>;

constexpr auto HIDDEN_VEHICLE	= 2;
constexpr auto EXTRA_PIXEL		= 320;
constexpr auto LEFT_BOUND		= -EXTRA_PIXEL;
constexpr auto RIGHT_BOUND		= SCREEN_WIDTH + EXTRA_PIXEL;
constexpr auto EXTEND_WIDTH		= SCREEN_WIDTH + EXTRA_PIXEL * 2;
constexpr auto BASE_X			= 0;
/*
BOUND			_____________				BOUND
||				|			|				||
||EXTRA_PIXEL	|	SCREEN	|EXTRA_PIXEL	||
||				|___________|				||
<---------------EXTEND_WIDTH----------------->
*/

constexpr float OBSTACLE_SIZE	= 85;
class Obstacle;

//function for init new vehicle
using obstacle_ptr = std::function < std::unique_ptr<Obstacle>(sf::Vector2f pos, const sf::Texture& texture, sf::IntRect textureBound) >;

class Lane {
public:
	enum class direction {
		left = 1,
		right = -1,
	};
	//Force moves constructor
	Lane() = default;
	Lane(Lane&&) = default;
	Lane(const sf::Vector2f road_pos, const direction, float speed);
	void			initObstacle(size_t);
	void			setType(obstacle_ptr, sf::Texture& vehicle, sf::IntRect vehicle_bound);
	size_t			getVehicleSize() const;
	Obstacle&		getVehicle(size_t);

	virtual void	update(float dt) = 0;
	virtual void	draw(sf::RenderTarget&) = 0;

	bool 			isPause() const;
	void			pause(bool = true);
protected:
	const sf::Vector2f						m_vehicle_pos = { 0.f,0.f };
	const direction							m_dir;
	float									m_speed = 0;
	std::vector<std::unique_ptr<Obstacle>>	m_vehicles;
	sf::Texture*							m_vehicles_texture = nullptr;
	sf::IntRect								m_texture_bound;
	obstacle_ptr							m_init_func;
	size_t									m_num_vehicle = MIN_VEHICLE;
	bool									is_paused = false;
};//base class

class D_Lane:public Lane {
public:	
	//Force moves constructor
	D_Lane()		 = default;
	D_Lane(D_Lane&&) = default;
	D_Lane(const sf::Vector2f road_pos, const direction, float speed);

	void update(float dt);	
	void draw(sf::RenderTarget&);
private:	
	TrafficLight							m_light;	
	sf::Time								m_red_time				= sf::seconds(1.5f + mtrand::getFloat(0, 1));
	sf::Time								m_green_time			= sf::seconds(4.f + mtrand::getFloat(0, 1));
	sf::Clock								m_clock;
	sf::Time								m_start_time_change_color = m_clock.getElapsedTime();//time start change color light
};

class A_Lane:public Lane {
public:
	A_Lane() = default;
	A_Lane(A_Lane&&) = default;
	A_Lane(const sf::Vector2f road_pos, const direction, float speed);

	void update(float dt);
	void draw(sf::RenderTarget&);
};

template<typename T>
std::unique_ptr<Lane> new_lane(const sf::Vector2f road_pos, const Lane::direction dir, float speed)
{
	return std::make_unique<T>(road_pos, dir, speed);
}
#endif // !_road_h
