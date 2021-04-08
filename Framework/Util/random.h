#ifndef _random
#define _random
#include<ctime>
#include<random>
#include"no_copy.h"
class random
{
private:
	std::mt19937 engine;
	template<typename Distribution, typename T>
	T get_number(T low, T high) {
		Distribution dist(low, high);
		return dist(engine);
	}
public:
	using uniform_int = std::uniform_int_distribution<>;
	using uniform_double = std::uniform_real_distribution<>;
	random(unsigned seed = std::time(nullptr));
	int		getInt		(int	low, int	high);
	double	getDouble	(double low, double high);
	float	getFloat	(float	low, float	high);
};
class mtrand : public no_copy {
private:
	mtrand() = default;
	random seed;
	static random& get();
public:
	static int		getInt		(int	low, int	high);
	static double	getDouble	(double low, double high);
	static float	getFloat	(float	low, float	high);
};
#endif 

