#include <testing_module.h>

std::shared_ptr<HeroUnit> TestingModule::getHeroUnitFromGame(std::shared_ptr<Game> game){
	return game->hero_unit;
}

std::vector<std::shared_ptr<Bullet>>& TestingModule::getEnemyUnitsBulletsFromGame(std::shared_ptr<Game> game){
	return game->enemy_units_bullets;
}

std::vector<std::shared_ptr<Bullet>>& TestingModule::getHeroUnitBulletsFromGame(std::shared_ptr<Game> game){
	return game->hero_unit_bullets;
}

std::vector<std::shared_ptr<EnemyUnit>>& TestingModule::getEnemyUnitsFromGame(std::shared_ptr<Game> game){
	return game->enemy_units;
}

int TestingModule::getEnemyUnitsAmountFromEnemyUnitsBooster(){
	return EnemyUnitsBooster::enemy_units.size();
}

std::shared_ptr<sf::Shape> TestingModule::callCreateUnitShapeFromCircleUnitsFactory(double unit_shape_size, sf::Color unit_shape_color){
	return CircleUnitsFactory::getInstance().createUnitShape(unit_shape_size, unit_shape_color);
}

std::shared_ptr<sf::Shape> TestingModule::callCreateUnitShapeFromSquareUnitsFactory(double unit_shape_size, sf::Color unit_shape_color){
	return SquareUnitsFactory::getInstance().createUnitShape(unit_shape_size, unit_shape_color);
}
