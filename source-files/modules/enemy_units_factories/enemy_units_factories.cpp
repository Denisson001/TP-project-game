#pragma once
#include "enemy_units_factories.h"

WeakEnemyUnit* CircleEnemyUnitsFactory::createWeakEnemyUnit(Vector position){
	WeakEnemyUnit* unit = new WeakEnemyUnit;

	unit->shape = new sf::CircleShape(CIRCLE_WEAK_ENEMY_SHAPE_SIZE);
	unit->shape->setFillColor(WEAK_ENEMY_SHAPE_COLOR);
	unit->shape->setOrigin(CIRCLE_WEAK_ENEMY_SHAPE_SIZE, CIRCLE_WEAK_ENEMY_SHAPE_SIZE);

	unit->position = position;

	return unit;
}

StrongEnemyUnit* CircleEnemyUnitsFactory::createStrongEnemyUnit(Vector position){
	StrongEnemyUnit* unit = new StrongEnemyUnit;

	unit->shape = new sf::CircleShape(CIRCLE_STRONG_ENEMY_SHAPE_SIZE);
	unit->shape->setFillColor(STRONG_ENEMY_SHAPE_COLOR);
	unit->shape->setOrigin(CIRCLE_STRONG_ENEMY_SHAPE_SIZE, CIRCLE_STRONG_ENEMY_SHAPE_SIZE);

	unit->position = position;

	return unit;
}

MightyEnemyUnit* CircleEnemyUnitsFactory::createMightyEnemyUnit(Vector position){
	MightyEnemyUnit* unit = new MightyEnemyUnit;

	unit->shape = new sf::CircleShape(CIRCLE_MIGHTY_ENEMY_SHAPE_SIZE);
	unit->shape->setFillColor(MIGHTY_ENEMY_SHAPE_COLOR);
	unit->shape->setOrigin(CIRCLE_MIGHTY_ENEMY_SHAPE_SIZE, CIRCLE_MIGHTY_ENEMY_SHAPE_SIZE);

	unit->position = position;

	return unit;
}

WeakEnemyUnit* SquareEnemyUnitsFactory::createWeakEnemyUnit(Vector position){
	WeakEnemyUnit* unit = new WeakEnemyUnit;

	unit->shape = new sf::RectangleShape(sf::Vector2f(SQUARE_WEAK_ENEMY_SHAPE_SIZE, SQUARE_WEAK_ENEMY_SHAPE_SIZE));
	unit->shape->setFillColor(WEAK_ENEMY_SHAPE_COLOR);
	unit->shape->setOrigin(SQUARE_WEAK_ENEMY_SHAPE_SIZE / 2, SQUARE_WEAK_ENEMY_SHAPE_SIZE / 2);

	unit->position = position;

	return unit;
}

StrongEnemyUnit* SquareEnemyUnitsFactory::createStrongEnemyUnit(Vector position){
	StrongEnemyUnit* unit = new StrongEnemyUnit;

	unit->shape = new sf::RectangleShape(sf::Vector2f(SQUARE_STRONG_ENEMY_SHAPE_SIZE, SQUARE_STRONG_ENEMY_SHAPE_SIZE));
	unit->shape->setFillColor(STRONG_ENEMY_SHAPE_COLOR);
	unit->shape->setOrigin(SQUARE_STRONG_ENEMY_SHAPE_SIZE / 2, SQUARE_STRONG_ENEMY_SHAPE_SIZE / 2);

	unit->position = position;

	return unit;
}

MightyEnemyUnit* SquareEnemyUnitsFactory::createMightyEnemyUnit(Vector position){
	MightyEnemyUnit* unit = new MightyEnemyUnit;

	unit->shape = new sf::RectangleShape(sf::Vector2f(SQUARE_MIGHTY_ENEMY_SHAPE_SIZE, SQUARE_MIGHTY_ENEMY_SHAPE_SIZE));
	unit->shape->setFillColor(MIGHTY_ENEMY_SHAPE_COLOR);
	unit->shape->setOrigin(SQUARE_MIGHTY_ENEMY_SHAPE_SIZE / 2, SQUARE_MIGHTY_ENEMY_SHAPE_SIZE / 2);

	unit->position = position;

	return unit;
}
