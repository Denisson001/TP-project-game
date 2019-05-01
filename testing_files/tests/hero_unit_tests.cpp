#include <boost/test/unit_test.hpp>

#include <game_proxy.h>
#include <fake_controller.h>
#include <enemy_units_decorators.h>
#include <testing_module.h>

#include <window_settings.h>
#include <units_settings.h>
#include <math_settings.h>

BOOST_AUTO_TEST_SUITE(HERO_UNIT)

std::shared_ptr<Game> initializeGame(std::string controller_string){
	GameProxy::initialize(CircleUnitsFactory::getInstance(), SquareUnitsFactory::getInstance(), std::make_shared<FakeController>(controller_string));
	return TestingModule::getGameInstance();
}

BOOST_AUTO_TEST_CASE(getController_method){
	std::shared_ptr<FakeController> controller = std::make_shared<FakeController>("00000000");
	GameProxy::initialize(CircleUnitsFactory::getInstance(), SquareUnitsFactory::getInstance(), controller);
	BOOST_CHECK(TestingModule::getHeroUnit(TestingModule::getGameInstance())->getController() == controller);
}

BOOST_AUTO_TEST_CASE(addBullet_method){
	std::shared_ptr<Game> game = initializeGame("00000000");
	std::shared_ptr<HeroUnit> hero_unit = TestingModule::getHeroUnit(game); 
	Vector direction = Vector(41, 43);
	TestingModule::addBullet(hero_unit, direction);
	std::vector<std::shared_ptr<Bullet>>& bullets = TestingModule::getHeroUnitBullets(game);
	BOOST_CHECK((int)bullets.size() == 1);
	BOOST_CHECK_CLOSE_FRACTION(hero_unit->getPosition().x, bullets[0]->position.x, eps9);
	BOOST_CHECK_CLOSE_FRACTION(hero_unit->getPosition().y, bullets[0]->position.y, eps9);
	BOOST_CHECK_CLOSE_FRACTION(hero_unit->getAttackRange(), bullets[0]->range, eps9);
	direction = direction.resize(BULLET_SPEED);
	BOOST_CHECK_CLOSE_FRACTION(direction.x, bullets[0]->vector.x, eps9);
	BOOST_CHECK_CLOSE_FRACTION(direction.y, bullets[0]->vector.y, eps9);
	BOOST_CHECK(hero_unit->getShape()->getFillColor() == bullets[0]->shape->getFillColor());
	BOOST_CHECK(hero_unit->getDamage() == bullets[0]->damage);
}

BOOST_AUTO_TEST_CASE(changeAttackModule_method){
	std::shared_ptr<Game> game = initializeGame("00000000");
	std::shared_ptr<HeroUnit> hero_unit = TestingModule::getHeroUnit(game); 
	for (int i = 0; i < 100; i++){
		BOOST_CHECK(TestingModule::getCurrentAttackModuleNumber(hero_unit) == i % 3);
		TestingModule::changeAttackModule(hero_unit);
	}
}

BOOST_AUTO_TEST_CASE(updateMovementModule_method_free_move){
	for (int mask = 0; mask < (1 << 4); mask++){
		std::string controller_string = "";
		for (int i = 0; i < 4; i++){
			controller_string += '0' + ((mask >> i) & 1);
		}
		int dx = ((mask >> 3) & 1) - ((mask >> 2) & 1);
		int dy = ((mask >> 1) & 1) - ((mask >> 0) & 1);
		std::shared_ptr<Game> game = initializeGame(controller_string + "0000");
		std::shared_ptr<HeroUnit> hero_unit = TestingModule::getHeroUnit(game); 
		Vector old_position = hero_unit->getPosition();
		double time = 50;
		Vector vector = Vector(dx, dy).resize(HERO_MOVESPEED * time);
		TestingModule::updateMovementModule(hero_unit, time);
		Vector new_position = hero_unit->getPosition();
		BOOST_CHECK_CLOSE_FRACTION(vector.x, (new_position - old_position).x, eps9);
		BOOST_CHECK_CLOSE_FRACTION(vector.y, (new_position - old_position).y, eps9);
	}
}

BOOST_AUTO_TEST_CASE(updateMovementModule_method_border){
	for (int mask = 0; mask < 4; mask++){
		std::string controller_string = "00000000";
		controller_string[mask] = '1';
		std::shared_ptr<Game> game = initializeGame(controller_string);
		std::shared_ptr<HeroUnit> hero_unit = TestingModule::getHeroUnit(game);
		double time = 1e9;
		TestingModule::updateMovementModule(hero_unit, time);
		BOOST_CHECK(hero_unit->getPosition().x >= -eps9);
		BOOST_CHECK(hero_unit->getPosition().y >= -eps9);
		BOOST_CHECK(hero_unit->getPosition().x <= WINDOW_WIDTH + eps9);
		BOOST_CHECK(hero_unit->getPosition().y <= WINDOW_HEIGHT + eps9);
	}
}

BOOST_AUTO_TEST_CASE(updateAttackModule_method_border){
	std::shared_ptr<Game> game = initializeGame("00001010");
	std::shared_ptr<HeroUnit> hero_unit = TestingModule::getHeroUnit(game); 
	double time = 1e9;
	TestingModule::updateAttackModule(hero_unit, time);
	BOOST_CHECK((int)TestingModule::getHeroUnitBullets(game).size() > 0);
}

BOOST_AUTO_TEST_SUITE_END()