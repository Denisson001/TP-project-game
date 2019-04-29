#include <boost/test/unit_test.hpp>

#include <testing_module.h>
#include <game_proxy.h>
#include <fake_controller.h>

#include <units_settings.h>

const double eps9 = 1e-9;

BOOST_AUTO_TEST_SUITE(ENEMY_UNIT)

std::shared_ptr<Game> initializeGame(){
    GameProxy::initialize(CircleUnitsFactory::getInstance(), SquareUnitsFactory::getInstance(), std::make_shared<FakeController>("00000000"));
    return GameProxy::getGameInstance();
}

void checkBulletsSettings(std::shared_ptr<EnemyUnit> enemy_unit, int bullets_amount){
	std::shared_ptr<Game> game = initializeGame();
	TestingModule::updateAttackModule(enemy_unit, enemy_unit->getMaxAttackCooldown() + eps9);
	std::vector<std::shared_ptr<Bullet>> bullets = TestingModule::getEnemyUnitsBullets(game);
	BOOST_CHECK((int)bullets.size() == bullets_amount);
	Vector direction = TestingModule::getHeroUnit(game)->getPosition() - enemy_unit->getPosition();
	int v = bullets_amount / 2;
	for (int i = -v; i <= v; i++){
		Vector vector = direction.resize(BULLET_SPEED).rotate(BULLET_DEFLECTION_ANGLE * i);
		BOOST_CHECK_CLOSE_FRACTION(vector.x, bullets[i + v]->vector.x, eps9);
		BOOST_CHECK_CLOSE_FRACTION(vector.y, bullets[i + v]->vector.y, eps9);
	}
}

void checkBulletsAmount(std::shared_ptr<EnemyUnit> enemy_unit, int bullets_amount){
	std::shared_ptr<Game> game = initializeGame();
	TestingModule::updateAttackModule(enemy_unit, enemy_unit->getMaxAttackCooldown() + eps9);
	BOOST_CHECK((int)TestingModule::getEnemyUnitsBullets(game).size() == bullets_amount);
	if (enemy_unit->getMaxAttackCooldown() >= eps9){
		TestingModule::updateAttackModule(enemy_unit, enemy_unit->getMaxAttackCooldown() / 2);
		BOOST_CHECK((int)TestingModule::getEnemyUnitsBullets(game).size() == bullets_amount);
		TestingModule::updateAttackModule(enemy_unit, enemy_unit->getMaxAttackCooldown() / 2 + eps9);
		BOOST_CHECK((int)TestingModule::getEnemyUnitsBullets(game).size() == 2 * bullets_amount);
	}
}

BOOST_AUTO_TEST_SUITE(WEAK_ENEMY_UNIT)

BOOST_AUTO_TEST_CASE(updateAttackModule_method_bullets_amount){
	checkBulletsAmount(CircleUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)), 1);
	checkBulletsAmount(SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)), 1);
}

BOOST_AUTO_TEST_CASE(updateAttackModule_method_bullets_settings){
	checkBulletsSettings(CircleUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)), 1);
	checkBulletsSettings(SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)), 1);
}

BOOST_AUTO_TEST_CASE(upgrade_method){
	initializeGame();
	std::shared_ptr<EnemyUnit> enemy_units[2] = {CircleUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)), 
												 SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0))};
	for (int i = 0; i < 2; i++){
		int health = enemy_units[i]->getHealth();
		enemy_units[i]->upgrade();
		BOOST_CHECK(enemy_units[i]->getHealth() == std::min(WEAK_ENEMY_MAX_HEALTH, health + WEAK_ENEMY_ADDITIONAL_HEALTH));
	}
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(STRONG_ENEMY_UNIT)

BOOST_AUTO_TEST_CASE(updateAttackModule_method_bullets_amount){
	checkBulletsAmount(CircleUnitsFactory::getInstance().createStrongEnemyUnit(Vector(0, 0)), 3);
	checkBulletsAmount(SquareUnitsFactory::getInstance().createStrongEnemyUnit(Vector(0, 0)), 3);
}

BOOST_AUTO_TEST_CASE(updateAttackModule_method_bullets_settings){
	checkBulletsSettings(CircleUnitsFactory::getInstance().createStrongEnemyUnit(Vector(0, 0)), 3);
	checkBulletsSettings(SquareUnitsFactory::getInstance().createStrongEnemyUnit(Vector(0, 0)), 3);
}

BOOST_AUTO_TEST_CASE(upgrade_method){
	initializeGame();
	std::shared_ptr<EnemyUnit> enemy_units[2] = {CircleUnitsFactory::getInstance().createStrongEnemyUnit(Vector(0, 0)), 
												 SquareUnitsFactory::getInstance().createStrongEnemyUnit(Vector(0, 0))};
	for (int i = 0; i < 2; i++){
		int max_attack_cooldown = enemy_units[i]->getMaxAttackCooldown();
		enemy_units[i]->upgrade();
		BOOST_CHECK(enemy_units[i]->getMaxAttackCooldown() == 
					std::max(STRONG_ENEMY_MIN_ATTACK_COOLDOWN, max_attack_cooldown * STRONG_ENEMY_ATTACK_COOLDOWN_REDUCTION_COEFFICIENT));
	}
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(MIGHTY_ENEMY_UNIT)

BOOST_AUTO_TEST_CASE(updateAttackModule_method_bullets_amount){
	checkBulletsAmount(CircleUnitsFactory::getInstance().createMightyEnemyUnit(Vector(0, 0)), 5);
	checkBulletsAmount(SquareUnitsFactory::getInstance().createMightyEnemyUnit(Vector(0, 0)), 5);
}

BOOST_AUTO_TEST_CASE(updateAttackModule_method_bullets_settings){
	checkBulletsSettings(CircleUnitsFactory::getInstance().createMightyEnemyUnit(Vector(0, 0)), 5);
	checkBulletsSettings(SquareUnitsFactory::getInstance().createMightyEnemyUnit(Vector(0, 0)), 5);
}

BOOST_AUTO_TEST_CASE(upgrade_method){
	initializeGame();
	std::shared_ptr<EnemyUnit> enemy_units[2] = {CircleUnitsFactory::getInstance().createMightyEnemyUnit(Vector(0, 0)), 
												 SquareUnitsFactory::getInstance().createMightyEnemyUnit(Vector(0, 0))};
	for (int i = 0; i < 2; i++){
		int attack_range = enemy_units[i]->getAttackRange();
		enemy_units[i]->upgrade();
		BOOST_CHECK(enemy_units[i]->getAttackRange() == 
					std::min(MIGHTY_ENEMY_MAX_ATTACK_RANGE, attack_range * MIGHTY_ENEMY_ADDITIONAL_ATTACK_RANGE_COEFFICIENT));
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()