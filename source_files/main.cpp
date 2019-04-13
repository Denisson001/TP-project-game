#include <string>
#include <memory>

#include <game_proxy.h>
#include <game.h>
#include <window.h>
#include <units_factories.h>

UnitsFactory& getFactory(const std::string& s){
	if (s == "Circle")
		return CircleUnitsFactory::getInstance();
	else
		return SquareUnitsFactory::getInstance();
}

int main(int argc, char* argv[]){
	UnitsFactory& enemy_units_factory = getFactory(std::string(argv[1]));
	UnitsFactory& hero_unit_factory = getFactory(std::string(argv[2]));

	std::shared_ptr<Game> game = std::make_shared<Game>(enemy_units_factory, hero_unit_factory);
	GameProxy::setGameInstance(game);
	Window window;
	sf::Clock clock;

	game->initialize();

	while (1){
		if (window.isClosed()) break;

		double time_delta = clock.getElapsedTime().asMilliseconds();
		clock.restart();

		game->update(time_delta);
		window.display(game);
	}
}
