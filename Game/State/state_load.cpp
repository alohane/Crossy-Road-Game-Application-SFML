#include "state_load.h"
#include"state_playing.h"

state_load::state_load(Game& game)
	: state_base(game)
	, load_menu(game.get_window(), 300, &asset::texture().get("blue_panel", "png"))
	, load_inf()
{
	background2.setTexture(&asset::texture().get("background2","png"));
	background2.setSize({1280,720 });

	background.setPosition({ 440,50 });
	background.setSize({ 400,100 });
	background.setFillColor(sf::Color::Red);
	background.setOutlineColor(sf::Color::Yellow);
	background.setOutlineThickness(4);

	fail_label.setCharacterSize(50);
	fail_label.setFillColor(sf::Color::White);
	fail_label.setOutlineColor(sf::Color::Black);
	fail_label.setPosition({ 490,60 });
	fail_label.setString(warning);

	auto Load_Textbox = makeTextBox(name);
	Load_Textbox->setLabel("Name");
	
	auto LoadBtn = makeButton();
	LoadBtn->setText("Load Game");
	LoadBtn->setFunction([&]() {
		if (loadGame(name, load_inf) == false)is_fail = true;
		else {
			if (game.getStateSize() == 2)
				this->game().swapState(std::make_unique<state_playing>(game, load_inf));
			if (game.getStateSize() == 3)
			{
				this->game().popState();
				this->game().swapState(std::make_unique<state_playing>(game, load_inf));
			}
		}
		});
	
	auto ReturnBtn = makeButton();
	ReturnBtn->setText("Return");
	ReturnBtn->setFunction([&]() {
		this->game().popState();
		});
	load_menu.addWidget(std::move(Load_Textbox));
	load_menu.addWidget(std::move(LoadBtn));
	load_menu.addWidget(std::move(ReturnBtn));
	load_menu.setTitle("Load", game.get_window());

}
void state_load::handleEvent(sf::Event e)
{
	load_menu.handleEvent(e, this->game().get_window());
}

void state_load::update(sf::Time delta_time)
{}

void state_load::draw(sf::RenderTarget& renderer)
{
	renderer.draw(background2);
	load_menu.render(renderer);
	if (is_fail)
	{
		renderer.draw(background);
		renderer.draw(fail_label);
	}
	
}
