#include <testing_module.h>

std::shared_ptr<HeroUnit> TestingModule::getHeroUnit(std::shared_ptr<Game> game){
	return game->hero_unit;
}

std::vector<std::shared_ptr<Bullet>>& TestingModule::getEnemyUnitsBullets(std::shared_ptr<Game> game){
	return game->enemy_units_bullets;
}

std::vector<std::shared_ptr<Bullet>>& TestingModule::getHeroUnitBullets(std::shared_ptr<Game> game){
	return game->hero_unit_bullets;
}

std::vector<std::shared_ptr<EnemyUnit>>& TestingModule::getEnemyUnits(std::shared_ptr<Game> game){
	return game->enemy_units;
}

int TestingModule::getEnemyUnitsAmount(){
	return EnemyUnitsBooster::enemy_units.size();
}

std::shared_ptr<sf::Shape> TestingModule::createCircleUnitShape(UnitsFactory& units_factory, double unit_shape_size, sf::Color unit_shape_color){
	return units_factory.createUnitShape(unit_shape_size, unit_shape_color);
}

std::pair<int, int> TestingModule::getDirectionFromController(std::shared_ptr<HeroUnitAttackModule> attack_module, std::shared_ptr<Controller> controller){
	return attack_module->getDirectionFromController(controller);
}

void TestingModule::updateAttackModule(std::shared_ptr<EnemyUnit> enemy_unit, double time){
	enemy_unit->updateAttackModule(time);
}
