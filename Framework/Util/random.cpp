#include "random.h"

random::random(unsigned seed)
	: engine(seed)
{}

int random::getInt(int low, int high)
{
	return get_number<uniform_int>(low, high);
}

double random::getDouble(double low, double high)
{
	return get_number<uniform_double>(low, high);
}

float random::getFloat(float low, float high)
{
	return (float)get_number<uniform_double>(low, high);
}

random& mtrand::get()
{
	static mtrand mersenne_twister;
	return mersenne_twister.seed;
}

int mtrand::getInt(int low, int high)
{
	return get().getInt(low, high);
}

double mtrand::getDouble(double low, double high)
{
	return get().getDouble(low, high);
}

float mtrand::getFloat(float low, float high)
{
	return get().getFloat(low, high);
}
