#ifndef _asset_storage
#define _asset_storage
//Singleton pattern
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"asset_manager.h"
#include"../Util/no_copy.h"
//Hold all resources, using singleton pattern
class asset : public no_copy
{
private:
	asset();
	asset_manager<sf::Font>			_font;			//fonts folder
	asset_manager<sf::Texture>		_texture;		//textures folder
	asset_manager<sf::SoundBuffer>	_sound_buffer;	//audio folder
public:
	static asset& get();
	static asset_manager<sf::Font>&			font();
	static asset_manager<sf::Texture>&		texture();
	static asset_manager<sf::SoundBuffer>&	sound();
};
#endif // !_asset_storage
