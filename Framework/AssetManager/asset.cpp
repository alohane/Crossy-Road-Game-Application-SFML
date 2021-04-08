#include "asset.h"
asset::asset()
    : _font         ("fonts")
    , _texture      ("textures")
    , _sound_buffer ("audio")
{}
asset& asset::get()
{
    static asset storage;
    return storage;
}

asset_manager<sf::Font>& asset::font()
{
    return get()._font;
}

asset_manager<sf::Texture>& asset::texture()
{
    return get()._texture;
}

asset_manager<sf::SoundBuffer>& asset::sound()
{
    return get()._sound_buffer;
}
