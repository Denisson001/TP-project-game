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

void TestingModule::updateMovementModule(std::shared_ptr<EnemyUnit> enemy_unit, double time){
	enemy_unit->updateMovementModule(time);
}

void TestingModule::updateAttackModule(std::shared_ptr<EnemyUnit> enemy_unit, double time){
	enemy_unit->updateAttackModule(time);
}

void TestingModule::updateMovementModule(std::shared_ptr<HeroUnit> hero_unit, double time){
	hero_unit->updateMovementModule(time);
}

void TestingModule::updateAttackModule(std::shared_ptr<HeroUnit> hero_unit, double time){
	hero_unit->updateAttackModule(time);
}

void TestingModule::addBullet(std::shared_ptr<HeroUnit> hero_unit, Vector direction){
	hero_unit->addBullet(direction);
}

void TestingModule::addBullet(std::shared_ptr<EnemyUnit> enemy_unit, Vector direction){
	enemy_unit->addBullet(direction);
}

void TestingModule::changeAttackModule(std::shared_ptr<HeroUnit> hero_unit){
	hero_unit->changeAttackModule();
}

int TestingModule::getCurrentAttackModuleNumber(std::shared_ptr<HeroUnit> hero_unit){
	return hero_unit->current_attack_module_number;
}

Vector TestingModule::convertGridCellToVector(std::shared_ptr<EnemyMovementDecorator> decorated_enemy_unit, std::pair<int, int> cell_index){
	return decorated_enemy_unit->convertGridCellToVector(cell_index);
}

void TestingModule::setNewGridPosition(std::shared_ptr<EnemyMovementDecorator> decorated_enemy_unit){
	decorated_enemy_unit->setNewGridPosition();
}

std::pair<int, int> TestingModule::getNewGridPosition(std::shared_ptr<EnemyMovementDecorator> decorated_enemy_unit){
	return decorated_enemy_unit->new_grid_position;
}