#include<iostream>
#include "Game.h"
#include "../Game/State/state_main_menu.h"
state_base& Game::cur_state() const
{
	return *m_states.top();
}
void Game::pop()
{
	m_pop_pending = false;
	m_states.pop();
}
void Game::swap()
{
	m_swap_pending = false;
	m_states.pop();
	m_states.push(std::move(m_swap_state));
}
Game::Game()
	//set resolution, window's title and disable fullscreen
	: m_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Crossy Road", sf::Style::Close)
{
	m_window.setFramerateLimit(60);
	sf::Image icon;
	//set icon for window, skip if failed
	if (icon.loadFromFile("Assets/icon.png"))
		m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	//Load all texture names
	m_txr_set.add_type("vehicle");
	m_txr_set.load_set("Config/car.txt", "vehicle");
	m_txr_set.load_set("Config/truck.txt", "vehicle");

	m_txr_set.add_type("animal");
	m_txr_set.load_set("Config/bird.txt", "animal");
	m_txr_set.load_set("Config/dino.txt", "animal");
	//push first state here
	pushState(std::make_unique<state_main_menu>(*this));
}

void Game::run()
{
	m_window.setKeyRepeatEnabled(false);
	//main game loop
	while (m_window.isOpen() && m_states.empty() == 0) {
		auto& state = cur_state();
		auto time = update_dt_clock();
		//Frame update
		//std::cout << 1.f / time.asSeconds() << std::endl;//DEBUG FPS
		state.update(time);
		//Handle event
		sf::Event event;
		while (m_window.pollEvent(event)) {
			state.handleEvent(event);
			state.handleInput();
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			default:
				break;
			}
		}
		//Render
		m_window.clear();
		state.draw(m_window);
		m_window.display();
		//Handle pending pop/swap state
		if (m_pop_pending)
			pop();
		if (m_swap_pending)
			swap();
	}
	m_window.close();//m_states is empty
}

void Game::pushState(std::unique_ptr<state_base> state)
{
	m_states.push(std::move(state));
}

void Game::popState()
{
	m_pop_pending = true;
}

void Game::swapState(std::unique_ptr<state_base> swap)
{
	m_swap_pending = true;
	m_swap_state = std::move(swap);
}

size_t Game::getStateSize() const
{
	return m_states.size();
}

const sf::RenderWindow& Game::get_window() const
{
	return m_window;
}

const txr_lookup& Game::get_txr_set() const
{
	return m_txr_set;
}

sf::Time Game::update_dt_clock()
{
	return m_dt_clock.restart();
}
