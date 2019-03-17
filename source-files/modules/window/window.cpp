#pragma once
#include "window.h"

Window::Window(): window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), WINDOW_NAME, sf::Style::Close){}

bool Window::is_closed(){
	sf::Event event;
	if (window.pollEvent(event)){
		if (event.type == sf::Event::Closed){
			window.close();
			return 1;
		}
	}
	return 0;
}

void Window::display(Game &game){
	window.clear();
	
	for (unit : game.enemyUnits){
		unit->shape->setPosition(unit->position.x, unit->position.y);
		window.draw(*unit->shape);
	}

	window.display();
}