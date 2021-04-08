#include "Player.h"
#include "../world.h"
#include <algorithm>

Player::Player() 
	: Collision(PLAYER_SIZE/2, PLAYER_SIZE/2)
	, m_player({ PLAYER_SIZE,PLAYER_SIZE })
	, player_texture(&asset::texture().get("player_sprite_2", "png"))
	, explosion(&asset::texture().get("explosion", "png"))
	, min_y_get_point(0)
	, nextspot(cur_pos.y - TILE_SIZE)
	, death_sound((asset::sound().get("oofMinecraft", "ogg")))
{
	m_player.setPosition(this->origin_pos);
	m_player.setTexture(player_texture);
	m_player.setTextureRect(sf::IntRect{ 0,192,64,64 });
	death_sound.setVolume(50);
}


void Player::input()
{
	/*input() and moving() functions are working together*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (is_walking == false)
		{
			nextspot = cur_pos.y - TILE_SIZE;
			moves[UP] = true;
			is_walking = true;
			initY = 192;
			initX = 0;
			m_player.setTextureRect({ initX,initY,64,64 });
			if (nextspot == -TILE_SIZE) {
				nextspot = origin_pos.y;
				cur_pos.y = SCREEN_HEIGHT;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (is_walking == false)
		{
			nextspot = cur_pos.y + TILE_SIZE;
			if (nextspot >= SCREEN_HEIGHT) {
				nextspot = cur_pos.y - TILE_SIZE;
				moves[DOWN] = false;
				is_walking = false;
			}
			else {
				moves[DOWN] = true;
				is_walking = true;
				initY = 0;
				initX = 0;
				m_player.setTextureRect({ initX,initY,64,64 });
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (is_walking == false)
		{
			nextspot = cur_pos.x - TILE_SIZE;
			if (nextspot <= TILE_SIZE * 2) {
				nextspot = cur_pos.x + TILE_SIZE;
				moves[DOWN] = false;
				is_walking = false;;
			}
			else {
				moves[LEFT] = true;
				is_walking = true;
				initY = 64;
				initX = 0;
				m_player.setTextureRect({ initX,initY,64,64 });
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (is_walking == false)
		{
			nextspot = cur_pos.x + TILE_SIZE;
			if (nextspot >= SCREEN_WIDTH - TILE_SIZE * 3) {
				nextspot = cur_pos.x - TILE_SIZE;
				moves[DOWN] = false;
				is_walking = false;;
			}
			else {
				moves[RIGHT] = true;
				is_walking = true;
				initY = 128;
				initX = 0;
				m_player.setTextureRect({ initX,initY,64,64 });
			}
		}
	}
}
void Player::moving()
{
	if (is_walking == true)
	{
		if (moves[UP] == true)
		{
			cur_pos.y -= movespeed;
			if (cur_pos.y <= nextspot)
			{
				cur_pos.y = nextspot;
				is_walking = false;
				moves[UP] = false;
			}
		}
		if (moves[DOWN] == true )
		{
			cur_pos.y += movespeed;
			if (cur_pos.y >= nextspot)
			{
				cur_pos.y = nextspot;
				is_walking = false;
				moves[DOWN] = false;
			}
		}
		if (moves[LEFT] == true)
		{
			cur_pos.x -= movespeed;
			if (cur_pos.x <= nextspot)
			{
				cur_pos.x = nextspot;
				is_walking = false;
				moves[LEFT] = false;
			}
		}
		if (moves[RIGHT] == true)
		{
			cur_pos.x += movespeed;
			if (cur_pos.x >= nextspot)
			{
				cur_pos.x = nextspot;
				is_walking = false;
				moves[RIGHT] = false;
			}
		}
		m_player.setPosition(cur_pos.x, cur_pos.y);
	}
}

const sf::Vector2f& Player::getPosition() const
{
	return m_player.getPosition();
}

void Player::onCollide(Collision& other)
{
	is_walking = false;
	m_player.setTexture(explosion);
	m_player.setScale(1.5f, 1.5f);
	is_Alive = false;
}

void Player::animationRenderer() {
	if (m_clock.getElapsedTime().asSeconds() > m_delay.asSeconds() && is_walking == true && is_Alive) {
		if (initX > 192) {
			initX = 0;
			m_player.setTextureRect({ initX,initY,64,64 });
		}
		else {
			m_player.setTextureRect({ initX,initY,64,64 });
			initX += 64;
		}
		m_clock.restart();
	}
	else if (m_clock.getElapsedTime().asSeconds() > m_delay.asSeconds() && !is_Alive) {
		m_player.setTextureRect({ initX,0,64,64 });
		initX += 64;
		m_clock.restart();
	}
}


void Player::draw(sf::RenderTarget& target)
{
	sf::Clock clock;
	target.draw(m_player);
}

bool Player::isAlive() const
{
	return is_Alive;
}

bool Player::isPassLevel() const
{
	return m_passed;
}

void Player::update()
{
	if (this->m_player.getGlobalBounds().top > 600)
		min_y_get_point = getPosition().y;		
	//PLEASE REMOVE THIS
	//score 90,270,450,630    
	if ((this->m_player.getGlobalBounds().top == 90
		|| this->m_player.getGlobalBounds().top == 270
		|| this->m_player.getGlobalBounds().top == 450)
		&& this->m_player.getGlobalBounds().top < min_y_get_point) {
		min_y_get_point = getPosition().y;
		m_get_score = true;
	}
	else
		m_get_score = false;
	if (getPosition().y <= SCREEN_HEIGHT && getPosition().y > SCREEN_HEIGHT - movespeed * 2) {
		m_passed = true;
		m_get_score = true;
	}
}

bool Player::isGetScore() const
{
	return m_get_score;
}

void Player::restart()
{
	m_passed = false;
	m_get_score = false;
	min_y_get_point = 720.f;
}

void Player::deathSoundPlaying()
{
	if (!is_Alive)death_sound.play();
}

void Player::setPosition(sf::Vector2f position)
{
	m_player.setPosition(position);
	cur_pos = position;
}
