#include <testing_module.h>


std::shared_ptr<sf::Shape> TestingModule::callCreateUnitShapeFromCircleUnitsFactory(double unit_shape_size, sf::Color unit_shape_color){
	return CircleUnitsFactory::getInstance().createUnitShape(unit_shape_size, unit_shape_color);
}

std::shared_ptr<sf::Shape> TestingModule::callCreateUnitShapeFromSquareUnitsFactory(double unit_shape_size, sf::Color unit_shape_color){
	return SquareUnitsFactory::getInstance().createUnitShape(unit_shape_size, unit_shape_color);
}

void TestingModule::callUpdateMovementModuleFromHeroUnit(std::shared_ptr<HeroUnit> unit,double time){
	unit->updateMovementModule(time);
}

UnitsFactory& TestingModule::getEnemyUnitsFactoryFromGame(Game& game){
	return game.enemy_units_factory;
}

std::shared_ptr<HeroUnit> TestingModule::getHeroUnitFromGame(Game& game){
	return game.hero_unit;
}