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

std::string Window::convertNumberToString(int value){
	if (value == 0)
		return "0";
	std::string text;
	bool minus = 0;
	if (value < 0){
		value = -value;
		minus = 1;
	}
	while(value){
		text += '0' + value % 10;
		value /= 10;
	}
	if (minus)
		text += '-';
	reverse(text.begin(), text.end());
	return text;
}

void Window::drawText(std::string str, Vector position){
	/*sf::Font font;
	font.loadFromFile("font.ttf");
	sf::Text text(str, font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Black);
	text.setPosition(position.x, position.y);
	// Draw it
	window.draw(text);*/
}

void Window::display(std::shared_ptr<Game> game){
	window.clear();

	for (auto& unit : game->enemy_units){
		unit->shape->setPosition(unit->position.x, unit->position.y);
		window.draw(*unit->shape);
	}

	for (auto& enemy_unit_bullet : game->enemy_bullets){
		enemy_unit_bullet->shape->setPosition(enemy_unit_bullet->position.x, enemy_unit_bullet->position.y);
		window.draw(*enemy_unit_bullet->shape);
	}

	for (auto& hero_unit_bullet : game->hero_unit->bullets){
		hero_unit_bullet->shape->setPosition(hero_unit_bullet->position.x, hero_unit_bullet->position.y);
		window.draw(*hero_unit_bullet->shape);
	}

	game->hero_unit->shape->setPosition(game->hero_unit->position.x, game->hero_unit->position.y);
	window.draw(*game->hero_unit->shape);

	window.display();
}
