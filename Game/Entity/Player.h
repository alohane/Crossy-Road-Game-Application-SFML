#ifndef Player_h
#define Player_h

#include"../../PCH.h"
#include "../Collidable.h"

/*
	Represents the player
*/
constexpr auto START_X		= SCREEN_WIDTH / 2;
constexpr auto START_Y		= SCREEN_HEIGHT - TILE_SIZE;
constexpr auto MOVESPEED	= 5.f;
constexpr auto PLAYER_SIZE	= TILE_SIZE - 10;

static int initX = 0;
static int initY = 192;

class Player :public Collision
{
public:
	Player();
	void draw(sf::RenderTarget& target);
	void update();
	void input();	//keypress detection
	void moving();	//moving if "walking" boolean is true
	void onCollide(Collision& other) override;
	void animationRenderer();
	void restart();
	void deathSoundPlaying();
	void setPosition(sf::Vector2f);
	const sf::Vector2f& getPosition() const;
	bool isAlive() const;
	bool isGetScore()const;
	bool isPassLevel()const;
private:
	sf::RectangleShape	m_player;
	sf::Clock			m_clock;
	sf::Time		    m_delay     = sf::seconds(0.1f);
	sf::Vector2f		origin_pos	= { START_X, START_Y };
	sf::Vector2f		cur_pos		= { START_X,START_Y };
	float				movespeed	= MOVESPEED;

	enum	MOVE { UP, DOWN, LEFT, RIGHT }; //enums instead of remember numbers
	bool	moves[4] = { 0,0,0,0 };
	bool	is_walking = false;
	float	nextspot; //the next tilespot of the map

	bool is_Alive = true;
	sf::Texture* player_texture;
	sf::Texture* explosion;
	float min_y_get_point;
	bool m_passed = false;
	bool m_get_score = false;

	sf::Sound death_sound;
};

#endif