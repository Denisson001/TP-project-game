#include <window.h>

Window::Window(): window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close){}

bool Window::isClosed(){
	sf::Event event;
	if (window.pollEvent(event)){
		if (event.type == sf::Event::Closed){
			window.close();
			return 1;
		}
	}
	return 0;
}

void Window::display(std::shared_ptr<Game> game){
	window.clear();

	for (auto& unit : game->enemy_units){
		unit->getShape()->setPosition(unit->getPosition().x, unit->getPosition().y);
		window.draw(*unit->getShape());
	}

	for (auto& enemy_unit_bullet : game->enemy_units_bullets){
		enemy_unit_bullet->shape->setPosition(enemy_unit_bullet->position.x, enemy_unit_bullet->position.y);
		window.draw(*enemy_unit_bullet->shape);
	}

	for (auto& hero_unit_bullet : game->hero_unit_bullets){
		hero_unit_bullet->shape->setPosition(hero_unit_bullet->position.x, hero_unit_bullet->position.y);
		window.draw(*hero_unit_bullet->shape);
	}

	game->hero_unit->getShape()->setPosition(game->hero_unit->getPosition().x, game->hero_unit->getPosition().y);
	window.draw(*game->hero_unit->getShape());

	window.display();
}
