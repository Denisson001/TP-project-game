#include <game.h>
#include <enemy_units_decorators.h>

#include <game_proxy.h>

Game::Game(UnitsFactory& enemy_units_factory, UnitsFactory& hero_unit_factory): enemy_units_factory(enemy_units_factory){
	for (int i = 1; i < HORIZONTAL_DOTS_AMOUNT; i++){
		for (int j = 1; j < VERTICAL_DOTS_AMOUNT; j++){
			grid[i][j] = 0;
		}
	}
	hero_unit = hero_unit_factory.createHeroUnit(Vector(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), std::make_shared<KeyboardController>());
}

#include <iostream>

void Game::initialize(){
	//only for example
	enemy_units.push_back(std::make_shared<EnemyMovementDecorator>(
		(std::make_shared<EnemySuperAttackDecorator>(enemy_units_factory.createWeakEnemyUnit(Vector(HORIZONTAL_GAP_SIZE, VERITCAL_GAP_SIZE))))));
	enemy_units.push_back(std::make_shared<EnemyMovementDecorator>(
		(std::make_shared<EnemySuperAttackDecorator>(enemy_units_factory.createWeakEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 2, VERITCAL_GAP_SIZE))))));
	enemy_units.push_back(std::make_shared<EnemyMovementDecorator>(
		(std::make_shared<EnemySuperAttackDecorator>(enemy_units_factory.createWeakEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 3, VERITCAL_GAP_SIZE))))));
	enemy_units.push_back(std::make_shared<EnemyMovementDecorator>(
		(std::make_shared<EnemySuperAttackDecorator>(enemy_units_factory.createStrongEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 3, VERITCAL_GAP_SIZE * 3))))));
	enemy_units.push_back(enemy_units_factory.createStrongEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 3, VERITCAL_GAP_SIZE * 4)));
	enemy_units.push_back(std::make_shared<EnemyMovementDecorator>(enemy_units_factory.createMightyEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 7 , VERITCAL_GAP_SIZE * 7))));
	enemy_units.push_back(std::make_shared<EnemyMovementDecorator>(enemy_units_factory.createMightyEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 7 , VERITCAL_GAP_SIZE * 1))));
	enemy_units.push_back(std::make_shared<EnemyMovementDecorator>(enemy_units_factory.createMightyEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 7 , VERITCAL_GAP_SIZE * 2))));
	enemy_units.push_back(std::make_shared<EnemyMovementDecorator>(enemy_units_factory.createMightyEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 7 , VERITCAL_GAP_SIZE * 3))));
	enemy_units.push_back(std::make_shared<EnemyMovementDecorator>(enemy_units_factory.createMightyEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 7 , VERITCAL_GAP_SIZE * 4))));
	enemy_units.push_back(std::make_shared<EnemyMovementDecorator>(enemy_units_factory.createMightyEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 7 , VERITCAL_GAP_SIZE * 5))));
	enemy_units.push_back(enemy_units_factory.createMightyEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 4 , VERITCAL_GAP_SIZE * 3)));
	enemy_units.push_back(enemy_units_factory.createMightyEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 4 , VERITCAL_GAP_SIZE * 6)));
	enemy_units.push_back(enemy_units_factory.createMightyEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 4 , VERITCAL_GAP_SIZE * 5)));
	enemy_units.push_back(enemy_units_factory.createMightyEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 4 , VERITCAL_GAP_SIZE * 7)));
	enemy_units.push_back(enemy_units_factory.createMightyEnemyUnit(Vector(HORIZONTAL_GAP_SIZE * 4 , VERITCAL_GAP_SIZE * 2)));
	//СТОЯЧИЕ ЗАНИМАЮТ КЛЕТКУ
	// + ПРИ УДАЛЕНИИ
}

void Game::checkHeroUnitBullets(){
	for (int i = 0; i < (int)hero_unit->bullets.size(); i++){
		sf::FloatRect bullet_bounds = hero_unit->bullets[i]->getBounds();
		bool deleted = 0;

		for (int j = 0; j < (int)enemy_units.size(); j++){
			sf::FloatRect enemy_unit_bounds = enemy_units[j]->getBounds();
			if (enemy_unit_bounds.intersects(bullet_bounds)){
				enemy_units[j]->health -= hero_unit->bullets[i]->damage;
				if (enemy_units[j]->health <= 0){
					std::swap(enemy_units[j], enemy_units.back());
					enemy_units.pop_back();
				}
				deleted = 1;
				break;
			}
		}

		if (deleted){
			std::swap(hero_unit->bullets[i], hero_unit->bullets.back());
			hero_unit->bullets.pop_back();
		}
	}
}

void Game::checkEnemyUnitsBullets(double time){
	sf::FloatRect hero_unit_bounds = hero_unit->getBounds();

	for (int i = 0; i < (int)enemy_bullets.size(); i++){
		enemy_bullets[i]->update(time);
		sf::FloatRect enemy_bullet_bounds = enemy_bullets[i]->getBounds();
		bool deleted = 0;

		if (hero_unit_bounds.intersects(enemy_bullet_bounds)){
			hero_unit->health -= enemy_bullets[i]->damage;
			deleted = 1;
		}

		if (enemy_bullets[i]->range <= 0){
			deleted = 1;
		}

		if (deleted){
			swap(enemy_bullets[i], enemy_bullets.back());
			enemy_bullets.pop_back();
		}
	}
}

void Game::update(double time){
	hero_unit->update(time);

	for (auto& enemy_unit : enemy_units)
		enemy_unit->update(time);

	checkHeroUnitBullets();
	checkEnemyUnitsBullets(time);
}
