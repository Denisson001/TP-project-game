#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>
#include <memory>

#include <geometry.h>
#include <controller.h>
#include <units.h>
#include <units_factories.h>
#include <units_settings.h>
#include <window_settings.h>

#include <testing_module.h>
#include <fake_controller.h>

const double eps0 = 1;
const double eps9 = 1e-9;


BOOST_AUTO_TEST_SUITE(HERO_UNIT)

BOOST_AUTO_TEST_CASE(update_movement_module){
	for (int mask = 0; mask < (1 << 4); mask++){
		bool up = (mask >> 0) & 1, down = (mask >> 1) & 1, left = (mask >> 2) & 1, right = (mask >> 3) & 1;
		Vector position(100, 200);
		double time = 50;

		std::shared_ptr<HeroUnit> unit1 = CircleUnitsFactory::getInstance().createHeroUnit(position, std::make_shared<FakeController>(up, down, left, right));
		std::shared_ptr<HeroUnit> unit2 = SquareUnitsFactory::getInstance().createHeroUnit(position, std::make_shared<FakeController>(up, down, left, right));
		TestingModule::callUpdateMovementModuleFromHeroUnit(unit1, (double)time / HERO_MOVE_SPEED);
		TestingModule::callUpdateMovementModuleFromHeroUnit(unit2, (double)time / HERO_MOVE_SPEED);

		int dx = 0, dy = 0;
		if (up) dy -= 1;
		if (down) dy += 1;
		if (left) dx -= 1;
		if (right) dx += 1;

		if (dx != 0 && dy != 0) time /= sqrt(2);

		position.x += dx * time;
		position.y += dy * time;

		BOOST_CHECK_CLOSE_FRACTION(unit1->position.x, position.x, eps9);
		BOOST_CHECK_CLOSE_FRACTION(unit1->position.y, position.y, eps9);
		BOOST_CHECK_CLOSE_FRACTION(unit2->position.x, position.x, eps9);
		BOOST_CHECK_CLOSE_FRACTION(unit2->position.y, position.y, eps9);
	}
}

BOOST_AUTO_TEST_CASE(check_border){
	for (int mask = 1; mask < (1 << 4); mask <<= 1){
		bool up = (mask >> 0) & 1, down = (mask >> 1) & 1, left = (mask >> 2) & 1, right = (mask >> 3) & 1;
		Vector position(100, 100);
		double time = 1e9;

		std::shared_ptr<HeroUnit> unit1 = CircleUnitsFactory::getInstance().createHeroUnit(position, std::make_shared<FakeController>(up, down, left, right));
		std::shared_ptr<HeroUnit> unit2 = SquareUnitsFactory::getInstance().createHeroUnit(position, std::make_shared<FakeController>(up, down, left, right));
		TestingModule::callUpdateMovementModuleFromHeroUnit(unit1, time);
		TestingModule::callUpdateMovementModuleFromHeroUnit(unit2, time);
	
		BOOST_CHECK(unit1->position.x >= CIRCLE_HERO_SHAPE_SIZE / 2 - eps0);
		BOOST_CHECK(unit1->position.y >= CIRCLE_HERO_SHAPE_SIZE / 2 - eps0);
		BOOST_CHECK(unit1->position.x <= WINDOW_WIDTH - CIRCLE_HERO_SHAPE_SIZE / 2 + eps0);
		BOOST_CHECK(unit1->position.y <= WINDOW_HEIGHT - CIRCLE_HERO_SHAPE_SIZE / 2 + eps0);

		BOOST_CHECK(unit2->position.x >= SQUARE_HERO_SHAPE_SIZE / 2 - eps0);
		BOOST_CHECK(unit2->position.y >= SQUARE_HERO_SHAPE_SIZE / 2 - eps0);
		BOOST_CHECK(unit2->position.x <= WINDOW_WIDTH - SQUARE_HERO_SHAPE_SIZE / 2 + eps0);
		BOOST_CHECK(unit2->position.y <= WINDOW_HEIGHT - SQUARE_HERO_SHAPE_SIZE / 2 + eps0);
	}
}

BOOST_AUTO_TEST_SUITE_END()