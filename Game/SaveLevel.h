#ifndef _save_level
#define _save_level
#include "../PCH.h"
constexpr auto SAVE_LANE = 6;
constexpr auto SAVE_DIR = "Save/";
constexpr auto HIGHSCORE_DIR = "Highscore/";
constexpr auto FILE_EXT = ".bin";
class SaveInf {
public:
	struct LaneInf {
		int		laneType;
		int		lanePos;
		int		obstacleType;		
		int		obstacleNum;
		int		direction;
		float	speed;
		LaneInf() = default;
		LaneInf(int laneType, int lanePos, int obstacleType, int obstacleNum, int dir, float speed);
	};
	SaveInf() = default;
	SaveInf(int, unsigned level, unsigned score, std::vector<LaneInf> roads);
	void		update_score(unsigned);
	void		update_level(unsigned);
	void		update_road(std::vector<LaneInf> new_roads);
	void		update_best_player_y(int);

	unsigned	get_level()				const;
	unsigned	get_score()				const;
	//number of lanes
	unsigned	get_size()				const;
	int			getBestLane()			const;
	const LaneInf& get_RoadInf(size_t)	const;
private:
	unsigned						m_level = 1;
	unsigned						m_score = 0;
	int								m_best_player_y = Y_TILES - 1;
	std::vector<LaneInf>			m_road_arr;
};
bool saveGame(std::string& file_name, const SaveInf&);
bool loadGame(std::string file_name, SaveInf&);
bool loadHighScore(int& highscore);
bool saveHighScore(const int& highscore);
#endif 
