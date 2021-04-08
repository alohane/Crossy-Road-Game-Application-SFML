#include"state_save.h"
state_save::state_save(Game& game, SaveInf& save)
	: state_base(game)
	, save_menu(game.get_window(), 300, &asset::texture().get("blue_panel", "png"))
	, m_save(save)
{

	background.setTexture(&asset::texture().get("background2", "png"));
	background.setSize({ 1280,720 });

	auto name_textbox = makeTextBox(m_name);
	name_textbox->setLabel("Name");

	auto SaveBtn = makeButton();
	SaveBtn->setText("Save Game");
	SaveBtn->setFunction([&]() {
		if (saveGame(m_name, m_save))
			this->game().popState();
		});

	auto ReturnBtn = makeButton();
	ReturnBtn->setText("Return Game");
	ReturnBtn->setFunction([&]() {
		this->game().popState();
		});
	save_menu.addWidget(std::move(name_textbox));
	save_menu.addWidget(std::move(SaveBtn));
	save_menu.addWidget(std::move(ReturnBtn));
	save_menu.setTitle("Save", game.get_window());

}

void state_save::handleEvent(sf::Event ev) {
	save_menu.handleEvent(ev, this->game().get_window());
}

void state_save::update(sf::Time delta_time)
{}

void state_save::draw(sf::RenderTarget& renderer) {
	renderer.draw(background);
	save_menu.render(renderer);
}
