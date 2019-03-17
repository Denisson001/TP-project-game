#pragma once
#include "game.h"

Game::Game(EnemyUnitsFactory *enemyUnitsFactory): enemyUnitsFactory(enemyUnitsFactory){
	spawnEnemyUnit();
}

void Game::spawnEnemyUnit(){
	int counter = 0;
	for (int i = 40; i <= 1240; i += 100){
		for (int j = 30; j <= 930; j += 100){
			switch(counter % 3){
				case 0: 
					enemyUnits.push_back(enemyUnitsFactory->createWeakEnemyUnit(Vector(i, j)));
					break;
				case 1: 
					enemyUnits.push_back(enemyUnitsFactory->createStrongEnemyUnit(Vector(i, j)));
					break;
				case 2: 
					enemyUnits.push_back(enemyUnitsFactory->createMightyEnemyUnit(Vector(i, j)));
			}
			counter++;
		}
	}
}	