#include "SaveLevel.h"
SaveInf::SaveInf(int max_y, unsigned level, unsigned score, std::vector<LaneInf> roads)
	: m_level(level)
	, m_score(score)
	, m_road_arr(roads)
	, m_best_player_y(max_y)
{}

SaveInf::LaneInf::LaneInf(int laneType, int lanePos, int obstacleType, int obstacleNum, int dir, float speed)
	: laneType(laneType)
	, lanePos(lanePos)
	, obstacleType(obstacleType)
	, obstacleNum(obstacleNum)
	, direction(dir)
	, speed(speed)
{}

unsigned SaveInf::get_level() const
{
	return m_level;
}
int SaveInf::getBestLane() const
{
	return m_best_player_y;
}
unsigned SaveInf::get_score() const
{
	return m_score;
}

unsigned SaveInf::get_size() const
{
	return m_road_arr.size();
}

const SaveInf::LaneInf& SaveInf::get_RoadInf(size_t idx) const
{
	return m_road_arr.at(idx);
}

void SaveInf::update_score(unsigned new_score)
{
	m_score = new_score;
}

void SaveInf::update_level(unsigned level)
{
	m_level = level;
}

void SaveInf::update_road(std::vector<LaneInf> new_roads)
{
	m_road_arr = new_roads;
}

void SaveInf::update_best_player_y(int maxY)
{
	m_best_player_y = maxY;
}



bool saveGame(std::string& file_name, const SaveInf& save)
{
	std::ofstream fout(SAVE_DIR + file_name + FILE_EXT, std::ios::binary);
	if (!fout.is_open())
		return false;
	unsigned lv = save.get_level(), score = save.get_score(), size = save.get_size();
	int maxY = save.getBestLane();
	fout.write((char*)&lv, sizeof(lv));
	fout.write((char*)&score, sizeof(score));
	fout.write((char*)&maxY, sizeof(maxY));
	fout.write((char*)&size, sizeof(size));
	fout.write((char*)&save.get_RoadInf(0), (long long)size * sizeof(SaveInf::LaneInf));
	fout.close();
	return true;
}

bool loadGame(std::string file_name, SaveInf& save)
{
	std::ifstream fin(SAVE_DIR + file_name + FILE_EXT, std::ios::binary);
	if (!fin.is_open())
		return false;
	unsigned lv, score, size;
	int maxY;
	sf::Vector2f position;
	fin.read((char*)&lv, sizeof(lv));
	fin.read((char*)&score, sizeof(score));
	fin.read((char*)&maxY, sizeof(maxY));
	fin.read((char*)&size, sizeof(size));
	std::vector<SaveInf::LaneInf> lanes(size);
	fin.read((char*)&lanes[0], (long long)size * sizeof(SaveInf::LaneInf));
	save = SaveInf(maxY, lv, score, lanes);
	fin.close();
	return true;
}
bool loadHighScore(int& highscore) {
	std::string filename = "highscore";
	std::ifstream fin(HIGHSCORE_DIR + filename + FILE_EXT, std::ios::binary);
	if (!fin.is_open())return false;
	fin.read((char*)&highscore, sizeof(int));
	fin.close();
	return true;
}
bool saveHighScore(const int& highscore) {
	std::string filename = "highscore";
	std::ofstream fout(HIGHSCORE_DIR + filename + FILE_EXT, std::ios::binary);
	if (!fout.is_open())return false;
	fout.write((char*)&highscore, sizeof(int));
	fout.close();
	return true;
}
