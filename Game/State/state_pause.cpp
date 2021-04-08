#include "state_pause.h"
#include"state_playing.h"
#include"state_save.h"
PauseMenu::PauseMenu(Game& game)
	: m_menu(game.get_window(), 250, &asset::texture().get("blue_panel", "png"))
{

	auto ResumeBtn = makeButton();
	ResumeBtn->setText("Resume");
	ResumeBtn->setFunction([&]() {
		m_isPaused = false;
		});
	auto SaveGameBtn = makeButton();
	SaveGameBtn->setText("Save Game");
	SaveGameBtn->setFunction([&]() {
		game.pushState(std::make_unique<state_save>(game, m_save));
		});
	auto LoadGameBtn = makeButton();
	LoadGameBtn->setText("Load Game");
	LoadGameBtn->setFunction([&]() {
		game.pushState(std::make_unique<state_load>(game));
		});
	auto ExitGameBtn = makeButton();
	ExitGameBtn->setText("Exit Game");
	ExitGameBtn->setFunction([&]() {
		game.popState();
		});
	m_menu.addWidget(std::move(ResumeBtn));
	m_menu.addWidget(std::move(SaveGameBtn));
	m_menu.addWidget(std::move(LoadGameBtn));
	m_menu.addWidget(std::move(ExitGameBtn));
	m_menu.setTitle("PAUSE  MENU", game.get_window());
}
void PauseMenu::update(sf::Time dental_time) {}

void PauseMenu::draw(sf::RenderTarget& target) {
	m_menu.render(target);
}
void PauseMenu::handleEvent(sf::Event ev,Game& game) {
	m_menu.handleEvent(ev, game.get_window());
}
bool PauseMenu::isPaused() {
	return m_isPaused;
}
void PauseMenu::changeState() {
	m_isPaused = !m_isPaused;
}
void PauseMenu::updateSaveInfo(SaveInf& save) {
	m_save = save;
}