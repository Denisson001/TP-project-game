#pragma once
#include "game.h"

Game::Game(UnitsFactory& enemy_units_factory, UnitsFactory& hero_unit_factory): enemy_units_factory(enemy_units_factory){
	hero = hero_unit_factory.createHeroUnit(Vector(500, 500));
	spawnEnemyUnit();
}

void Game::update(double time){
	hero->update(time);
	for (auto& unit : enemy_units) unit->update(time);
}

void Game::spawnEnemyUnit(){
	int counter = 0;
	for (int i = 40; i <= 640; i += 100){
		for (int j = 30; j <= 430; j += 100){
			switch(counter % 3){
				case 0: 
					enemy_units.push_back(enemy_units_factory.createWeakEnemyUnit(Vector(i, j)));
					break;
				case 1: 
					enemy_units.push_back(enemy_units_factory.createStrongEnemyUnit(Vector(i, j)));
					break;
				case 2: 
					enemy_units.push_back(enemy_units_factory.createMightyEnemyUnit(Vector(i, j)));
			}
			counter++;
		}
	}
}	