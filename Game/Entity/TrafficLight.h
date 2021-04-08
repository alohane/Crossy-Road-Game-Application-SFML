#ifndef trafflight_h
#define trafflight_h
#include"../../Framework/AssetManager/asset.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class TrafficLight {
private:
	sf::Texture* Red_Light;
	sf::Texture* Green_Light;
	sf::RectangleShape light;
	sf::Vector2f size = { 45.f,45.f };
	sf::Color state=(sf::Color::Green);
	sf::Clock time;	
public:
	TrafficLight(sf::Vector2f org_Pos);
	void turnRed();
	void turnGreen();
	sf::Color getLightState();
	void draw(sf::RenderTarget& target);
};


#endif