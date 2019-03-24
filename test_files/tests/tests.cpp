#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>
#include <memory>

#include <settings/units_settings.h>
#include <settings/window_settings.h>

const double eps2 = 1e-2;
const double eps9 = 1e-9;

/* ============================================================== GEOMETRY ============================================================== */

#include <modules/geometry/geometry.cpp>

BOOST_AUTO_TEST_SUITE(geometry)

BOOST_AUTO_TEST_CASE(vector){
	Vector v(4.2, -4.2);
	BOOST_CHECK_CLOSE_FRACTION(v.x, 4.2, eps9);
	BOOST_CHECK_CLOSE_FRACTION(v.y, -4.2, eps9);
}

BOOST_AUTO_TEST_SUITE_END()

/* =========================================================== UNITS FACTORIES ========================================================== */

#include <modules/units_factories/units_factories.cpp>

BOOST_AUTO_TEST_SUITE(units_factories)

template<class UnitType, class ShapeType>
void checkUnit(std::shared_ptr<Unit> unit, Vector position, sf::Color color, double shape_size){
	BOOST_CHECK_CLOSE_FRACTION(unit->position.x, position.x, eps9);
	BOOST_CHECK_CLOSE_FRACTION(unit->position.y, position.y, eps9);
	BOOST_CHECK_CLOSE_FRACTION(unit->shape->getLocalBounds().width / shape_size, 1, eps2);
	BOOST_CHECK_CLOSE_FRACTION(unit->shape->getLocalBounds().height / shape_size, 1, eps2);
	BOOST_CHECK(dynamic_cast<UnitType*>(unit.get()));
	BOOST_CHECK(unit->shape->getFillColor() == color);
	BOOST_CHECK(dynamic_cast<ShapeType*>(unit.get()->shape.get()));
}

/* ============================================= CIRCLE ============================================= */

BOOST_AUTO_TEST_CASE(circleUnitsFactoryPatternSingleton){
	UnitsFactory& circle_units_factory1 = CircleUnitsFactory::getInstance();
	UnitsFactory& circle_units_factory2 = CircleUnitsFactory::getInstance();
	BOOST_REQUIRE_EQUAL(&circle_units_factory1, &circle_units_factory2);
}

BOOST_AUTO_TEST_CASE(circleWeakEnemyUnit){
	std::shared_ptr<Unit> unit = CircleUnitsFactory::getInstance().createWeakEnemyUnit(Vector(4.2, -4.2));
	checkUnit<WeakEnemyUnit, sf::CircleShape>(unit, Vector(4.2, -4.2), WEAK_ENEMY_SHAPE_COLOR, CIRCLE_WEAK_ENEMY_SHAPE_SIZE * 2);
}

BOOST_AUTO_TEST_CASE(circleStrongkEnemyUnit){
	std::shared_ptr<Unit> unit = CircleUnitsFactory::getInstance().createStrongEnemyUnit(Vector(-23, 31));
	checkUnit<StrongEnemyUnit, sf::CircleShape>(unit, Vector(-23, 31), STRONG_ENEMY_SHAPE_COLOR, CIRCLE_STRONG_ENEMY_SHAPE_SIZE * 2);
}

BOOST_AUTO_TEST_CASE(circleMightyEnemyUnit){
	std::shared_ptr<Unit> unit = CircleUnitsFactory::getInstance().createMightyEnemyUnit(Vector(-666, -999));
	checkUnit<MightyEnemyUnit, sf::CircleShape>(unit, Vector(-666, -999), MIGHTY_ENEMY_SHAPE_COLOR, CIRCLE_MIGHTY_ENEMY_SHAPE_SIZE * 2);
}

BOOST_AUTO_TEST_CASE(circleHeroUnit){
	std::shared_ptr<Unit> unit = CircleUnitsFactory::getInstance().createHeroUnit(Vector(5, 10));
	checkUnit<HeroUnit, sf::CircleShape>(unit, Vector(5, 10), HERO_SHAPE_COLOR, CIRCLE_HERO_SHAPE_SIZE * 2);
}

/* ============================================= SQUARE ============================================= */

BOOST_AUTO_TEST_CASE(squareUnitsFactoryPatternSingleton){
	UnitsFactory& circle_units_factory1 = SquareUnitsFactory::getInstance();
	UnitsFactory& circle_units_factory2 = SquareUnitsFactory::getInstance();
	BOOST_REQUIRE_EQUAL(&circle_units_factory1, &circle_units_factory2);
}

BOOST_AUTO_TEST_CASE(squareWeakEnemyUnit){
	std::shared_ptr<Unit> unit = SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(123, 321));
	checkUnit<WeakEnemyUnit, sf::RectangleShape>(unit, Vector(123, 321), WEAK_ENEMY_SHAPE_COLOR, SQUARE_WEAK_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(squareStrongkEnemyUnit){
	std::shared_ptr<Unit> unit = SquareUnitsFactory::getInstance().createStrongEnemyUnit(Vector(555, 111));
	checkUnit<StrongEnemyUnit, sf::RectangleShape>(unit, Vector(555, 111), STRONG_ENEMY_SHAPE_COLOR, SQUARE_STRONG_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(squareMightyEnemyUnit){
	std::shared_ptr<Unit> unit = SquareUnitsFactory::getInstance().createMightyEnemyUnit(Vector(-77, -88));
	checkUnit<MightyEnemyUnit, sf::RectangleShape>(unit, Vector(-77, -88), MIGHTY_ENEMY_SHAPE_COLOR, SQUARE_MIGHTY_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(squareHeroUnit){
	std::shared_ptr<Unit> unit = SquareUnitsFactory::getInstance().createHeroUnit(Vector(10, 5));
	checkUnit<HeroUnit, sf::RectangleShape>(unit, Vector(10, 5), HERO_SHAPE_COLOR, SQUARE_HERO_SHAPE_SIZE);
}

BOOST_AUTO_TEST_SUITE_END()