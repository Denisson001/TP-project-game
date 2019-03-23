#pragma once
#include "window.h"

Window::Window(): window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), WINDOW_NAME, sf::Style::Close){}

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

	game.hero->shape->setPosition(game.hero->position.x, game.hero->position.y);
	window.draw(*game.hero->shape);

	window.display();
}
