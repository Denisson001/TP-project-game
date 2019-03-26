#include <game.h>

Game::Game(UnitsFactory& enemy_units_factory, UnitsFactory& hero_unit_factory): enemy_units_factory(enemy_units_factory){
	hero_unit = hero_unit_factory.createHeroUnit(Vector(700, 700), std::make_shared<KeyboardController>());
	
	//only for example
	int counter = 0;
	for (int i = 40; i <= 640; i += 100){
		for (int j = 30; j <= 430; j += 100){
			if (counter % 3 == 0) enemy_units.push_back(enemy_units_factory.createWeakEnemyUnit(Vector(i, j)));
			if (counter % 3 == 1) enemy_units.push_back(enemy_units_factory.createStrongEnemyUnit(Vector(i, j)));
			if (counter % 3 == 2) enemy_units.push_back(enemy_units_factory.createMightyEnemyUnit(Vector(i, j)));
			counter++;
		}
	}
}

void Game::update(double time){
	hero_unit->update(time);
	for (auto& unit : enemy_units) unit->update(time);
}