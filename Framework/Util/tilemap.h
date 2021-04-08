#ifndef _tile_map_h
#define _tile_map_h
#include<SFML/Graphics.hpp>
class TileMap :public sf::Drawable, public sf::Transformable {
private:
	sf::VertexArray		m_vertices;
	sf::Vector2u		m_tileSize;
	sf::Texture* m_texture = nullptr;
	unsigned			m_width = 0;
	unsigned			m_height = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	TileMap(sf::Texture* tileSet = nullptr, const sf::Vector2u& tileSize = {});
	void setTexture(sf::Texture* tileSet, const sf::Vector2u& tileSize);
	void setMapSize(unsigned num_tiles_x, unsigned num_tiles_y);
	//Each element in vector represent a row, therefore a row will have the same texture
	bool create_map(const std::vector<unsigned> vertical_tiles, const sf::Vector2u& renderSize);
};
#endif // !_tile_map_h
