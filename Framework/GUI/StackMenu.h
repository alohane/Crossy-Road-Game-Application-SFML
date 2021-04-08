#ifndef _STACKMENU_H_
#define  _STACKMENU_H_
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include"../../Framework/GUI/Widget.h"
class StackMenu
{
private:
    void initWidget(Widget&);
    std::vector<std::unique_ptr<Widget>>    _widgets;
    sf::RectangleShape                      _background;
    sf::Vector2f                            _base_pos;
    sf::Vector2f                            _base_size;
    Widget::Text                            _title_text;
public:
    StackMenu(const sf::RenderWindow& window, float baseY, const sf::Texture* texture = nullptr);
    StackMenu(const sf::Vector2f& position);
    StackMenu(StackMenu&& other)                noexcept;
    StackMenu& operator =(StackMenu&& other)    noexcept;
    ~StackMenu()                               = default;
    void addWidget(std::unique_ptr<Widget> w);
    void setTitle(const std::string& title, const sf::RenderTarget& target);
    void handleEvent(sf::Event e, const sf::RenderWindow& window);
    void render(sf::RenderTarget& renderer);
};
#endif // !_STACKMENU_H_
