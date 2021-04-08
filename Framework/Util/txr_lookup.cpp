#include "txr_lookup.h"

bool txr_set::loadFromFile(const std::string& dir)
{
	std::ifstream fin(dir);
	if (!fin)
		return false;
	std::string file_name, file_ext;
	sf::Vector2u size, file_dim;
	while (fin >> file_name >> file_ext 
		>> size.x >> size.y >> file_dim.x >> file_dim.y) 
	{
		m_set.emplace_back(file_name, file_ext, size, file_dim);
	}
	fin.close();
	return true;
}

size_t txr_set::size() const
{
	return m_set.size();
}

const std::string& txr_set::getName(size_t idx) const
{
	return m_set[idx].name;
}

const std::string& txr_set::getExt(size_t idx) const
{
	return m_set[idx].ext;
}

const txr_inf& txr_set::getFullInf(size_t idx) const
{
	return m_set[idx];
}

txr_inf::txr_inf(const std::string& name, const std::string& ext, sf::Vector2u size, sf::Vector2u fileDimension)
	: name(name)
	, ext(ext)
	, size(size)
	, fileDim(fileDimension)
{}

sf::IntRect txr_inf::getBounds(size_t idx) const
{
	int tu = idx % (fileDim.x / size.x);
	int tv = idx / (fileDim.x / size.x);
	return sf::IntRect(sf::Vector2i(tu * size.x, tv * size.y), sf::Vector2i(size));
}

size_t txr_inf::numTexture() const
{
	return (fileDim.x / size.x) * (fileDim.y / size.y);
}

lane_inf::lane_inf(float minSpeed, float maxSpeed, unsigned minObst, unsigned maxObst)
	: m_speed({minSpeed,maxSpeed})
	, m_obstacle({minObst,maxObst})
{}

void txr_lookup::add_type(const std::string& key)
{
	m_set.emplace(key, std::vector<txr_set>());
}

bool txr_lookup::load_set(const std::string& file_dir, const std::string& type)
{
	txr_set lookup;
	if (!lookup.loadFromFile(file_dir))
		return false;
	m_set.at(type).push_back(lookup);
	return true;
}

size_t txr_lookup::size() const
{
	return m_set.size();
}

const std::vector<txr_set>& txr_lookup::operator[](const std::string& key) const
{
	return m_set.at(key);
}




limit<float> lane_inf::speed()
{
	return m_speed;
}

limit<unsigned> lane_inf::obstacle()
{
	return m_obstacle;
}

const lane_inf& config_file::level(size_t idx)
{
	return m_level[idx];
}

bool config_file::loadFromFile(const std::string& dir)
{
	std::ifstream fin(dir);
	if (!fin)
		return false;
	float minSpeed, maxSpeed;
	int level, minObst, maxObst;
	while (fin >> level >> minSpeed >> maxSpeed >> minObst >> maxObst) {
		m_level.emplace_back(minSpeed, maxSpeed, minObst, maxObst);
	}
	fin.close();
	return true;
}

