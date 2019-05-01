#include <string>
#include <memory>
#include <iostream>

#include <game.h>
#include <window.h>
#include <units_factories.h>
#include <controller.h>

#include <game_proxy.h>
#include <logging_module.h>

#include <technical_settings.h>

UnitsFactory& getFactory(const std::string& s){
    if (s == "Circle"){
        return CircleUnitsFactory::getInstance();
    } else {
        return SquareUnitsFactory::getInstance();
    }
}

void printStatistics(){
    std::cout << "*** GAME OVER ***\n";
    std::cout << "You killed " << GameProxy::getKilledEnemyUnitsAmount() << " enemy units!\n";
    std::cout << "Time: " << (int)(GameProxy::getTime() / 1000) / 60 << " minutes " << (int)(GameProxy::getTime() / 1000) % 60 << " seconds\n";
}

int main(int argc, char* argv[]){
    int seed = abs(atoi(argv[3]));
    srand(seed);

    UnitsFactory& enemy_units_factory = getFactory(std::string(argv[1]));
    UnitsFactory& hero_unit_factory = getFactory(std::string(argv[2]));

    if (MAKE_LOGS){
        LoggingModule::initialize(seed);
    }
    GameProxy::initialize(hero_unit_factory, enemy_units_factory, std::make_shared<KeyboardController>());
    Window window;
    sf::Clock clock;

    while (1){
        if (window.isClosed() || GameProxy::end()){
            break;
        }
        double time_delta = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        GameProxy::update(time_delta);
        window.display();
    }

    printStatistics();
}
