#include "TrafficLight.h"
#include <vector>
#include <initializer_list>

TrafficLight::TrafficLight(sf::Vector2f org_Pos)
	: Green_Light(&asset::texture().get("green", "png"))
	, Red_Light(&asset::texture().get("red", "png"))
{

	this->light.setSize(size);
	this->light.setPosition(org_Pos);
	light.setTexture(Green_Light);
}

void TrafficLight::turnRed()
{
	state = (sf::Color::Red);
	light.setTexture(Red_Light);
}

void TrafficLight::turnGreen()
{
	state = (sf::Color::Green);
	light.setTexture(Green_Light);
}

sf::Color TrafficLight::getLightState()
{
	return state;
}

void TrafficLight::draw(sf::RenderTarget& target)
{
	target.draw(this->light);
	//std::cout << "draw light\n";
}