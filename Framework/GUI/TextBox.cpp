#include "Textbox.h"

TextBox::TextBox(std::string& modString)
	: m_pModString(&modString)
{
	_label.setCharacterSize(15);
	_rect.setFillColor({ 52, 152, 219 });
	_rect.setSize({ 256, 64 });
}

void TextBox::setTexture(const sf::Texture& tex) {
	_rect.setTexture(&tex);
}

void TextBox::setLabel(const std::string& str)
{
	_label.setString(str);
}

void TextBox::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
	handleClick(e, window);
	handleTextInput(e);
}

void TextBox::render(sf::RenderTarget& renderer)
{
	if (!_isActive) {
		_rect.setFillColor({ 52, 152, 219 });
	}
	else {
		_rect.setFillColor({ 82, 132, 239 });
	}
	renderer.draw(_rect);
	renderer.draw(_label);
	renderer.draw(_text);
}

void TextBox::setPosition(const sf::Vector2f& pos)
{
	_pos = pos;

	_rect.setPosition(_pos);
	_label.setPosition(_pos.x,
		_pos.y + _label.getGlobalBounds().height -
		_rect.getGlobalBounds().height / 2);
	_text.setPosition(_pos);
	_text.move(5, _rect.getGlobalBounds().height / 2.5f);
}

sf::Vector2f TextBox::getSize() const
{
	return  { _rect.getSize().x,
				_rect.getSize().y + _label.getGlobalBounds().height };
}

void TextBox::handleClick(sf::Event e, const sf::RenderWindow& window)
{
	auto pos = sf::Mouse::getPosition(window);

	if (_rect.getGlobalBounds().contains((float)pos.x, (float)pos.y))
	{
		if (e.type == sf::Event::MouseButtonPressed)
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				_isActive = true;
			}
		}
	}
	else
	{
		if (e.type == sf::Event::MouseButtonPressed)
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				_isActive = false;
			}
		}
	}
}

void TextBox::handleTextInput(sf::Event e)
{
	switch (e.type) {
	case sf::Event::TextEntered:
		if (_isActive) {
			//Get the key that was entered
			unsigned char keyCode = e.text.unicode;

			if (isValidCharacter(keyCode)) {
				if (_text.getGlobalBounds().width + 30 <= _rect.getGlobalBounds().width) {
					m_pModString->push_back(keyCode);
				}

			}
			else if (isBackspace(keyCode)) {
				//prevents popping back an empty string
				if (m_pModString->length() > 0)
					m_pModString->pop_back();
			}
			_text.setString(*m_pModString);
		}
		break;

	default:
		break;
	}
}

bool TextBox::isValidCharacter(unsigned char keyCode)
{
	return  keyCode >= 48 && keyCode <= 57 ||  //Numbers
		keyCode >= 65 && keyCode <= 90 ||  //Uppercase
		keyCode >= 97 && keyCode <= 122 ||  //Lowercase
		keyCode == 32;    //Space
}

bool TextBox::isBackspace(unsigned char keycode)
{
	return keycode == 8;
}



