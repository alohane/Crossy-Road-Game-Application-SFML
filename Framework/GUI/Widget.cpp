#include "Widget.h"
#include "../AssetManager/asset.h"
Widget::Text::Text()
	: Text(DEFAULT_FONT, DEFAULT_EXT,
		TEXT_SIZE,
		OUTLINE_COLOR, FILL_COLOR)
{}

Widget::Text::Text(const std::string& font, const std::string& ext, unsigned size, const sf::Color& outline, const sf::Color& fill)
{
	setCharacterSize(size);
	setOutlineColor(outline);
	setFillColor(fill);
	setOutlineThickness(2);
	setFont(asset::font().get(font, ext));
}

void setOriginCenter(sf::Transformable& obj, const sf::FloatRect& local_bound)
{
	obj.setOrigin(local_bound.left + local_bound.width / 2.0f
		, local_bound.top + local_bound.height / 2.0f);
}

void setPosCenter(sf::Transformable& obj, const sf::FloatRect& global_bound)
{
	obj.setPosition(getCenter(global_bound));
}

sf::Vector2f getCenter(const sf::FloatRect& global_bound)
{
	return { global_bound.left + global_bound.width / 2.0f
		, global_bound.top + global_bound.height / 2.0f };
}
