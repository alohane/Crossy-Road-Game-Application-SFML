#ifndef _iofile
#define _iofile
#include<string>
#include<vector>
#include<fstream>
#include<SFML/Graphics.hpp>
#include"no_copy.h"
struct txr_inf {
	const std::string	name;
	const std::string	ext;
	const sf::Vector2u	size;//texture dimensons (not file dimensions)
	const sf::Vector2u	fileDim;
	txr_inf(const std::string& name, const std::string& ext, sf::Vector2u size, sf::Vector2u fileDimension);
	sf::IntRect getBounds(size_t)	const;
	size_t		numTexture()		const;
};

//Contain file texture name and it size, load from file
class txr_set {
private:
	std::vector<txr_inf> m_set;//e.g: car1, car2, car3...
public:
	bool				loadFromFile(const std::string&);
	size_t				size()				const;
	const std::string&	getName(size_t)		const;
	const std::string&	getExt(size_t)		const;
	const txr_inf&		getFullInf(size_t)	const;
};
//Contain multiple file names of multiple texture objects
class txr_lookup : public no_copy {
public:
	void	add_type(const std::string&);
	//load new set of textures to available type (use add_type to add new type)
	bool	load_set(const std::string& file_dir, const std::string& type);
	size_t	size() const;
	const std::vector<txr_set>& operator[](const std::string&) const;
private:
	std::map<std::string, std::vector<txr_set>> m_set;//e.g: car, truck...
	//std::vector<txr_set> m_set;
};

//DEPRECATED
template<typename T>
struct limit {
	T min = 0, max = 0;
};
//DEPRECATED
class lane_inf {
private:
	limit<float> m_speed;
	limit<unsigned> m_obstacle;
public:
	lane_inf(float minSpeed, float maxSpeed, unsigned minObst, unsigned maxObst);
	limit<float> speed();
	limit<unsigned> obstacle();
};
//DEPRECATED
class config_file : public no_copy {
private:
	std::vector<lane_inf> m_level;
public: 
	const lane_inf& level(size_t);
	bool loadFromFile(const std::string&);
};
#endif // !_iofile
