#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>
#include <memory>

#include "../source_files/settings/units_settings.h"

/* ============================================================== GEOMETRY ============================================================== */

#include "../source_files/modules/geometry/geometry.cpp"

BOOST_AUTO_TEST_SUITE(geometry)

BOOST_AUTO_TEST_CASE(vector){
	Vector v(4.2, -4.2);
	BOOST_CHECK_CLOSE_FRACTION(v.x, 4.2, 1e-9);
	BOOST_CHECK_CLOSE_FRACTION(v.y, -4.2, 1e-9);
}

BOOST_AUTO_TEST_SUITE_END()

/* =========================================================== UNITS FACTORIES ========================================================== */

#include "../source_files/modules/units_factories/units_factories.cpp"

BOOST_AUTO_TEST_SUITE(units_factories)

/* ============================================= CIRCLE ============================================= */

BOOST_AUTO_TEST_CASE(circleUnitsFactoryPatternSingleton){
	UnitsFactory& circle_units_factory1 = CircleUnitsFactory::getInstance();
	UnitsFactory& circle_units_factory2 = CircleUnitsFactory::getInstance();
	BOOST_REQUIRE_EQUAL(&circle_units_factory1, &circle_units_factory2);
}

BOOST_AUTO_TEST_CASE(circleWeakEnemyunit){
	std::shared_ptr<WeakEnemyUnit> unit = CircleUnitsFactory::getInstance().createWeakEnemyUnit(Vector(4.2, -4.2));
	BOOST_CHECK_CLOSE_FRACTION(unit->position.x, 4.2, 1e-9);
	BOOST_CHECK_CLOSE_FRACTION(unit->position.y, -4.2, 1e-9);
	BOOST_CHECK(unit->shape->getFillColor() == sf::Color::Red);
	BOOST_CHECK_CLOSE_FRACTION(unit->shape->getOrigin().x, CIRCLE_WEAK_ENEMY_SHAPE_SIZE, 1e-9);
	BOOST_CHECK(dynamic_cast<sf::CircleShape*>(unit.get()->shape.get()));
}


BOOST_AUTO_TEST_SUITE_END()