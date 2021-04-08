#ifndef _TEXTBOX_H_
#define  _TEXTBOX_H_
#include"../../Framework/GUI/Widget.h"
#include<functional>
class TextBox : public Widget
{
private:
	void handleClick(sf::Event e, const sf::RenderWindow& window);
	void handleTextInput(sf::Event);

	bool isValidCharacter(unsigned char keyCode);
	bool isBackspace(unsigned char keycode);

	sf::Vector2f    _pos;
	sf::RectangleShape       _rect;
	Text            _text;
	Text            _label;
	std::string* m_pModString;
	bool _isActive = false;
public:
	TextBox(std::string& modString);
	void setLabel(const std::string& str);
	void setTexture(const sf::Texture& tex);
	void handleEvent(sf::Event e, const sf::RenderWindow& window)   override;
	void render(sf::RenderTarget& renderer)                         override;
	void setPosition(const sf::Vector2f& pos)                       override;
	sf::Vector2f getSize() const                                    override;
};
inline std::unique_ptr<TextBox> makeTextBox(std::string& modStr) { return std::make_unique<TextBox>(modStr); }

#endif // !_TEXTBOX_H_