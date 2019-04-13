#include <units_factories.h>

#include <game_proxy.h>

void UnitsFactory::setUnitSettings(std::shared_ptr<Unit> unit, Vector position, double attack_cooldown, double attack_range, int damage, int health){
	unit->position = position;
	unit->max_attack_cooldown = attack_cooldown;
	unit->current_attack_cooldown = attack_cooldown;
	unit->attack_range = attack_range;
	unit->damage = damage;
	unit->health = health;
}

void UnitsFactory::setEnemyUnitGridPosition(std::shared_ptr<EnemyUnit> enemy_unit){
	enemy_unit->updateGridPosition();
	GameProxy::setGridCellValue(enemy_unit->current_grid_position, 1);
}

/* ========================= CIRCLE ========================= */

std::shared_ptr<sf::Shape> CircleUnitsFactory::createUnitShape(double unit_shape_size, sf::Color unit_shape_color){
	std::shared_ptr<sf::Shape> shape = std::make_shared<sf::CircleShape>(unit_shape_size / 2);
	shape->setFillColor(unit_shape_color);
	shape->setOrigin(unit_shape_size / 2, unit_shape_size / 2);
	return shape;
}

std::shared_ptr<WeakEnemyUnit> CircleUnitsFactory::createWeakEnemyUnit(Vector position){
	std::shared_ptr<WeakEnemyUnit> unit = std::make_shared<WeakEnemyUnit>();
	unit->shape = createUnitShape(CIRCLE_WEAK_ENEMY_SHAPE_SIZE, WEAK_ENEMY_SHAPE_COLOR);
	setUnitSettings(unit, position, CIRCLE_WEAK_ENEMY_ATTACK_COOLDOWN, WEAK_ENEMY_ATTACK_RANGE, CIRCLE_WEAK_ENEMY_DAMAGE, WEAK_ENEMY_HEALTH);
	setEnemyUnitGridPosition(unit);
	return unit;
}

std::shared_ptr<StrongEnemyUnit> CircleUnitsFactory::createStrongEnemyUnit(Vector position){
	std::shared_ptr<StrongEnemyUnit> unit = std::make_shared<StrongEnemyUnit>();
	unit->shape = createUnitShape(CIRCLE_STRONG_ENEMY_SHAPE_SIZE, STRONG_ENEMY_SHAPE_COLOR);
	setUnitSettings(unit, position, CIRCLE_STRONG_ENEMY_ATTACK_COOLDOWN, STRONG_ENEMY_ATTACK_RANGE, CIRCLE_STRONG_ENEMY_DAMAGE, STRONG_ENEMY_HEALTH);
	setEnemyUnitGridPosition(unit);
	return unit;
}

std::shared_ptr<MightyEnemyUnit> CircleUnitsFactory::createMightyEnemyUnit(Vector position){
	std::shared_ptr<MightyEnemyUnit> unit = std::make_shared<MightyEnemyUnit>();
	unit->shape = createUnitShape(CIRCLE_MIGHTY_ENEMY_SHAPE_SIZE, MIGHTY_ENEMY_SHAPE_COLOR);
	setUnitSettings(unit, position, CIRCLE_MIGHTY_ENEMY_ATTACK_COOLDOWN, MIGHTY_ENEMY_ATTACK_RANGE, CIRCLE_MIGHTY_ENEMY_DAMAGE, MIGHTY_ENEMY_HEALTH);
	setEnemyUnitGridPosition(unit);
	return unit;
}

std::shared_ptr<HeroUnit> CircleUnitsFactory::createHeroUnit(Vector position, std::shared_ptr<Controller> controller){
	std::shared_ptr<HeroUnit> unit = std::make_shared<HeroUnit>();
	unit->shape = createUnitShape(CIRCLE_HERO_SHAPE_SIZE, HERO_SHAPE_COLOR);
	unit->controller = controller;
	setUnitSettings(unit, position, CIRCLE_HERO_ATTACK_COOLDOWN, HERO_ATTACK_RANGE, CIRCLE_HERO_DAMAGE, HERO_HEALTH);
	return unit;
}

CircleUnitsFactory& CircleUnitsFactory::getInstance(){
	static CircleUnitsFactory circle_units_factory;
	return circle_units_factory;
}

/* ========================= SQUARE ========================= */

std::shared_ptr<sf::Shape> SquareUnitsFactory::createUnitShape(double unit_shape_size, sf::Color unit_shape_color){
	std::shared_ptr<sf::Shape> shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(unit_shape_size, unit_shape_size));
	shape->setFillColor(unit_shape_color);
	shape->setOrigin(unit_shape_size / 2, unit_shape_size / 2);
	return shape;
}

std::shared_ptr<WeakEnemyUnit> SquareUnitsFactory::createWeakEnemyUnit(Vector position){
	std::shared_ptr<WeakEnemyUnit> unit = std::make_shared<WeakEnemyUnit>();
	unit->shape = createUnitShape(SQUARE_WEAK_ENEMY_SHAPE_SIZE, WEAK_ENEMY_SHAPE_COLOR);
	setUnitSettings(unit, position, SQUARE_WEAK_ENEMY_ATTACK_COOLDOWN, WEAK_ENEMY_ATTACK_RANGE, SQUARE_WEAK_ENEMY_DAMAGE, WEAK_ENEMY_HEALTH);
	setEnemyUnitGridPosition(unit);
	return unit;
}

std::shared_ptr<StrongEnemyUnit> SquareUnitsFactory::createStrongEnemyUnit(Vector position){
	std::shared_ptr<StrongEnemyUnit> unit = std::make_shared<StrongEnemyUnit>();
	unit->shape = createUnitShape(SQUARE_STRONG_ENEMY_SHAPE_SIZE, STRONG_ENEMY_SHAPE_COLOR);
	setUnitSettings(unit, position, SQUARE_STRONG_ENEMY_ATTACK_COOLDOWN, STRONG_ENEMY_ATTACK_RANGE, SQUARE_STRONG_ENEMY_DAMAGE, STRONG_ENEMY_HEALTH);
	setEnemyUnitGridPosition(unit);
	return unit;
}

std::shared_ptr<MightyEnemyUnit> SquareUnitsFactory::createMightyEnemyUnit(Vector position){
	std::shared_ptr<MightyEnemyUnit> unit = std::make_shared<MightyEnemyUnit>();
	unit->shape = createUnitShape(SQUARE_MIGHTY_ENEMY_SHAPE_SIZE, MIGHTY_ENEMY_SHAPE_COLOR);
	setUnitSettings(unit, position, SQUARE_MIGHTY_ENEMY_ATTACK_COOLDOWN, MIGHTY_ENEMY_ATTACK_RANGE, SQUARE_MIGHTY_ENEMY_DAMAGE, MIGHTY_ENEMY_HEALTH);
	setEnemyUnitGridPosition(unit);
	return unit;
}

std::shared_ptr<HeroUnit> SquareUnitsFactory::createHeroUnit(Vector position, std::shared_ptr<Controller> controller){
	std::shared_ptr<HeroUnit> unit = std::make_shared<HeroUnit>();
	unit->shape = createUnitShape(SQUARE_STRONG_ENEMY_SHAPE_SIZE, HERO_SHAPE_COLOR);
	unit->controller = controller;
	setUnitSettings(unit, position, SQUARE_HERO_ATTACK_COOLDOWN, HERO_ATTACK_RANGE, SQUARE_HERO_DAMAGE, HERO_HEALTH);
	return unit;
}

SquareUnitsFactory& SquareUnitsFactory::getInstance(){
	static SquareUnitsFactory square_units_factory;
	return square_units_factory;
}
