#pragma once
#include "units_factories.h"

/* =============================================================== CIRCLE =============================================================== */

std::shared_ptr<sf::Shape> CircleUnitsFactory::createUnitShape(double unit_shape_size, sf::Color unit_shape_color){
	std::shared_ptr<sf::Shape> shape = std::make_shared<sf::CircleShape>(unit_shape_size);
	shape->setFillColor(unit_shape_color);
	shape->setOrigin(unit_shape_size, unit_shape_size);
	return shape;
}

std::shared_ptr<WeakEnemyUnit> CircleUnitsFactory::createWeakEnemyUnit(Vector position){
	std::shared_ptr<WeakEnemyUnit> unit = std::make_shared<WeakEnemyUnit>();
	unit->shape = createUnitShape(CIRCLE_WEAK_ENEMY_SHAPE_SIZE, WEAK_ENEMY_SHAPE_COLOR);
	unit->position = position;
	return unit;
}

std::shared_ptr<StrongEnemyUnit> CircleUnitsFactory::createStrongEnemyUnit(Vector position){
	std::shared_ptr<StrongEnemyUnit> unit = std::make_shared<StrongEnemyUnit>();
	unit->shape = createUnitShape(CIRCLE_STRONG_ENEMY_SHAPE_SIZE, STRONG_ENEMY_SHAPE_COLOR);
	unit->position = position;
	return unit;
}

std::shared_ptr<MightyEnemyUnit> CircleUnitsFactory::createMightyEnemyUnit(Vector position){
	std::shared_ptr<MightyEnemyUnit> unit = std::make_shared<MightyEnemyUnit>();
	unit->shape = createUnitShape(CIRCLE_MIGHTY_ENEMY_SHAPE_SIZE, MIGHTY_ENEMY_SHAPE_COLOR);
	unit->position = position;
	return unit;
}

std::shared_ptr<HeroUnit> CircleUnitsFactory::createHeroUnit(Vector position){
	std::shared_ptr<HeroUnit> unit = std::make_shared<HeroUnit>();
	unit->shape = createUnitShape(CIRCLE_HERO_SHAPE_SIZE, HERO_SHAPE_COLOR);
	unit->position = position;
	return unit;
}

CircleUnitsFactory& CircleUnitsFactory::getInstance(){
	static CircleUnitsFactory circle_units_factory;
	return circle_units_factory;
}

/* =============================================================== SQUARE =============================================================== */

std::shared_ptr<sf::Shape> SquareUnitsFactory::createUnitShape(double unit_shape_size, sf::Color unit_shape_color){
	std::shared_ptr<sf::Shape> shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(unit_shape_size, unit_shape_size));
	shape->setFillColor(unit_shape_color);
	shape->setOrigin(unit_shape_size / 2, unit_shape_size / 2);
	return shape;
}

std::shared_ptr<WeakEnemyUnit> SquareUnitsFactory::createWeakEnemyUnit(Vector position){
	std::shared_ptr<WeakEnemyUnit> unit = std::make_shared<WeakEnemyUnit>();
	unit->shape = createUnitShape(SQUARE_WEAK_ENEMY_SHAPE_SIZE, WEAK_ENEMY_SHAPE_COLOR);
	unit->position = position;
	return unit;
}

std::shared_ptr<StrongEnemyUnit> SquareUnitsFactory::createStrongEnemyUnit(Vector position){
	std::shared_ptr<StrongEnemyUnit> unit = std::make_shared<StrongEnemyUnit>();
	unit->shape = createUnitShape(SQUARE_STRONG_ENEMY_SHAPE_SIZE, STRONG_ENEMY_SHAPE_COLOR);
	unit->position = position;
	return unit;
}

std::shared_ptr<MightyEnemyUnit> SquareUnitsFactory::createMightyEnemyUnit(Vector position){
	std::shared_ptr<MightyEnemyUnit> unit = std::make_shared<MightyEnemyUnit>();
	unit->shape = createUnitShape(SQUARE_MIGHTY_ENEMY_SHAPE_SIZE, MIGHTY_ENEMY_SHAPE_COLOR);
	unit->position = position;
	return unit;
}

std::shared_ptr<HeroUnit> SquareUnitsFactory::createHeroUnit(Vector position){
	std::shared_ptr<HeroUnit> unit = std::make_shared<HeroUnit>();
	unit->shape = createUnitShape(SQUARE_STRONG_ENEMY_SHAPE_SIZE, HERO_SHAPE_COLOR);
	unit->position = position;
	return unit;
}

SquareUnitsFactory& SquareUnitsFactory::getInstance(){
	static SquareUnitsFactory square_units_factory;
	return square_units_factory;
}