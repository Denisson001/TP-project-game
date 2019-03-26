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

void Window::display(const Game &game){
	window.clear();
	
	for (auto& unit : game.enemy_units){
		unit->shape->setPosition(unit->position.x, unit->position.y);
		window.draw(*unit->shape);
	}

	game.hero_unit->shape->setPosition(game.hero_unit->position.x, game.hero_unit->position.y);
	window.draw(*game.hero_unit->shape);

	window.display();
}
