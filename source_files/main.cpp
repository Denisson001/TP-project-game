#include <string>
#include <memory>

#include <game.h>
#include <window.h>
#include <units_factories.h>

#include <game_proxy.h>
#include <logging_module.h>

#include <technical_settings.h>

UnitsFactory& getFactory(const std::string& s){
	if (s == "Circle")
		return CircleUnitsFactory::getInstance();
	else
		return SquareUnitsFactory::getInstance();
}

int main(int argc, char* argv[]){
	int seed = abs(atoi(argv[3]));
	srand(seed);

	UnitsFactory& enemy_units_factory = getFactory(std::string(argv[1]));
	UnitsFactory& hero_unit_factory = getFactory(std::string(argv[2]));

	if (MAKE_LOGS)
		LoggingModule::initialize(seed);
	std::shared_ptr<Game> game = std::make_shared<Game>(enemy_units_factory);
	GameProxy::setGameInstance(game);
	game->initialize(hero_unit_factory);
	Window window;
	sf::Clock clock;

	while (1){
		if (window.isClosed()) break;

		double time_delta = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		game->update(time_delta);
		window.display(game);
	}
}
