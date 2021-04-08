#ifndef _WIDGET_H_
#define _WIDGET_H_
#include <SFML/Graphics.hpp>
#include <memory>
//default value
#define	OUTLINE_COLOR	sf::Color::Black
#define FILL_COLOR		sf::Color::White
constexpr auto TEXT_SIZE	= 30;
constexpr auto DEFAULT_FONT = "arcade";
constexpr auto DEFAULT_EXT	= "TTF";
class Widget
{
public:
	virtual void handleEvent(sf::Event e, const sf::RenderWindow& window)   = 0;
	virtual void render     (sf::RenderTarget& renderer)                    = 0;
	virtual void setPosition(const sf::Vector2f& pos)                       = 0;
	virtual sf::Vector2f getSize() const                                    = 0;
	class Text : public sf::Text
	{
	public:
		Text();
		Text(const std::string& font, 
			const std::string& ext,
			unsigned size,
			const sf::Color& outline, 
			const sf::Color& fill);
	};
};
//move origin point to the center of the object
void setOriginCenter(sf::Transformable&, const sf::FloatRect& local_bound);
//align object to the center of other object
void setPosCenter(sf::Transformable&, const sf::FloatRect& global_bound);

sf::Vector2f getCenter(const sf::FloatRect& global_bound);
#endif //!_WIDGET_H_
