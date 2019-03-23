#include "modules/game/game.cpp"
#include "modules/window/window.cpp"
#include "modules/units_factories/units_factories.cpp"

#include <iostream>
#include <string>
#include <memory>

UnitsFactory& getFactory(const std::string& s){
	if (s == "Circle")
		return CircleUnitsFactory::getInstance();
	else 
		return SquareUnitsFactory::getInstance();
}

int main(int argc, char* argv[]){
	UnitsFactory& enemy_units_factory = getFactory(std::string(argv[1]));
	UnitsFactory& hero_unit_factory = getFactory(std::string(argv[2]));

	Game game(enemy_units_factory, hero_unit_factory);
	Window window;
	sf::Clock clock;

	while (!window.isClosed()){
		double time_delta = clock.getElapsedTime().asMicroseconds() / (double)800;
		clock.restart();

		while(time_delta >= 3){
			game.update(3);
			time_delta -= 3;
		}
		
		game.update(time_delta);
		window.display(game);
	}
}
