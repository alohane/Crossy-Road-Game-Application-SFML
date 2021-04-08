#include "state_main_menu.h"
#include "state_playing.h"
#include "state_load.h"
constexpr auto MUSIC_DIR = "Assets/audio/Cold_Youth.ogg";
constexpr auto MUSIC_VOL = 50;
state_main_menu::state_main_menu(Game& game)
	: state_base(game)
	, m_mainMenu(game.get_window(), 300, &asset::texture().get("blue_panel", "png"))
	, m_background(asset::texture().get("background768", "png"), { 768,448 }, { 8,12 }, sf::seconds(0.2f))
{
	//open and play background playlist
	initMusic(m_music, MUSIC_DIR, MUSIC_VOL);
	//Set up main menu
	sf::Texture& banner_texture = asset::texture().get("crossyroad3", "png");
	m_banner.setTexture(&banner_texture);
	m_banner.setSize(sf::Vector2f(banner_texture.getSize()));
	m_banner.setScale({ 2.5f,2.5f });
	m_banner.setFillColor(sf::Color::White);
	m_banner.setOutlineColor(sf::Color::Black);
	setOriginCenter(m_banner, m_banner.getLocalBounds());
	m_banner.setPosition(SCREEN_WIDTH / 2, 100.f);

	//Create buttons and assign function to it
	auto playBtn = makeButton();
	playBtn->setText("Play game");
	playBtn->setFunction([&]() {
		(this->game()).pushState(std::make_unique<state_playing>(game));
		m_music.pause();
		});

	auto LoadGameBtn = makeButton();
	LoadGameBtn->setText("Load Game");
	LoadGameBtn->setFunction([&]() {
		(this->game()).pushState(std::make_unique<state_load>(game));
		m_music.pause();
		});

	auto exitBtn = makeButton();
	exitBtn->setText("Exit game");
	exitBtn->setFunction([&]() {
		this->game().popState();
		});

	m_mainMenu.addWidget(std::move(playBtn));
	m_mainMenu.addWidget(std::move(LoadGameBtn));
	m_mainMenu.addWidget(std::move(exitBtn));
	m_mainMenu.setTitle("Choose   Action", game.get_window());
}

void state_main_menu::handleEvent(sf::Event ev)
{
	m_mainMenu.handleEvent(ev,this->game().get_window());
}

void state_main_menu::update(sf::Time delta_time)
{
	if (m_music.getStatus() == sf::Music::Paused) {
		m_music.play();
	}
}

void state_main_menu::draw(sf::RenderTarget& render)
{
	m_background.draw(render);
	m_mainMenu.render(render);
	render.draw(m_banner);
}
