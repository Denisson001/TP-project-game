#include "modules/game/game.cpp"
#include "modules/window/window.cpp"
#include "modules/enemy_units_factories/enemy_units_factories.cpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[]){
	EnemyUnitsFactory *enemyUnitsFactory = nullptr;
	if (std::string(argv[1]) == "Circle") enemyUnitsFactory = new CircleEnemyUnitsFactory;
	if (std::string(argv[1]) == "Square") enemyUnitsFactory = new SquareEnemyUnitsFactory;
    Game game(enemyUnitsFactory);
    Window window;
    sf::Clock clock;

    while (!window.is_closed()){
        double time_delta = clock.getElapsedTime().asMicroseconds() / 800;
        clock.restart();
        //std::cout << time_delta << std::endl;
        //game.update(time_delta);
        window.display(game);
    }
}
