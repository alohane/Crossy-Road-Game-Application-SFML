#include"tilemap.h"

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset tileSet
	states.texture = m_texture;

	// draw the vertex array
	target.draw(m_vertices, states);
}

TileMap::TileMap(sf::Texture* tileSet, const sf::Vector2u& tileSize)
	: m_texture(tileSet)
	, m_tileSize(tileSize)
{
	m_vertices.setPrimitiveType(sf::Quads);
}

void TileMap::setTexture(sf::Texture* tileSet, const sf::Vector2u& tileSize)
{
	m_texture = tileSet;
	m_tileSize = tileSize;
}

void TileMap::setMapSize(unsigned num_tiles_x, unsigned num_tiles_y)
{
	m_width = num_tiles_x;
	m_height = num_tiles_y;
	// resize the vertex array to fit the level size
	m_vertices.resize(m_width * m_height * 4);
}
bool TileMap::create_map(const std::vector<unsigned> vertical_tiles, const sf::Vector2u& renderSize)
{
	if (m_texture == nullptr || vertical_tiles.size() < m_height)
		return false;
	// populate the vertex array, with one quad per tile
	for (size_t i = 0; i < m_height; ++i) {
		size_t tile = vertical_tiles[i];
		// find its position in the tileset texture
		int tu = tile % (m_texture->getSize().x / m_tileSize.x);
		int tv = tile / (m_texture->getSize().x / m_tileSize.x);
		for (size_t j = 0; j < m_width; ++j) {
			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(j + i * m_width) * 4];
			// define its 4 corners
			float x = (float)renderSize.x, y = (float)renderSize.y;
			quad[0].position = sf::Vector2f(j * x		, i * y);
			quad[1].position = sf::Vector2f((j + 1) * x	, i * y);
			quad[2].position = sf::Vector2f((j + 1) * x	, (i + 1) * y);
			quad[3].position = sf::Vector2f(j * x		, (i + 1) * y);
			// define its 4 tileSet coordinates
			x = (float)m_tileSize.x; y = (float)m_tileSize.y;
			quad[0].texCoords = sf::Vector2f(tu * x			, tv * y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * x	, tv * y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * x	, (tv + 1) * y);
			quad[3].texCoords = sf::Vector2f(tu * x			, (tv + 1) * y);
		}
	}
	return true;
}
