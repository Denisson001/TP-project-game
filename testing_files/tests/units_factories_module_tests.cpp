#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>
#include <memory>

#include <controller.h>
#include <units_factories.h>
#include <units_settings.h>

#include <testing_module.h>

const double eps2 = 1e-2;
const double eps9 = 1e-9;

template<class UnitType, class ShapeType>
void checkUnit(std::shared_ptr<Unit> unit, Vector position, sf::Color color, double shape_size){
	BOOST_CHECK_CLOSE_FRACTION(unit->position.x, position.x, eps9);
	BOOST_CHECK_CLOSE_FRACTION(unit->position.y, position.y, eps9);
	BOOST_CHECK_CLOSE_FRACTION(unit->shape->getLocalBounds().width / shape_size, 1, eps2);
	BOOST_CHECK_CLOSE_FRACTION(unit->shape->getLocalBounds().height / shape_size, 1, eps2);
	BOOST_CHECK(dynamic_cast<UnitType*>(unit.get()));
	BOOST_CHECK(unit->shape->getFillColor() == color);
	BOOST_CHECK(dynamic_cast<ShapeType*>(unit->shape.get()));
}

BOOST_AUTO_TEST_SUITE(CIRCLE_UNITS_FACTORY)

BOOST_AUTO_TEST_CASE(units_factory_pattern_singleton){
	UnitsFactory& circle_units_factory1 = CircleUnitsFactory::getInstance();
	UnitsFactory& circle_units_factory2 = CircleUnitsFactory::getInstance();
	BOOST_REQUIRE_EQUAL(&circle_units_factory1, &circle_units_factory2);
}

BOOST_AUTO_TEST_CASE(weak_enemy_unit){
	std::shared_ptr<EnemyUnit> unit = CircleUnitsFactory::getInstance().createWeakEnemyUnit(Vector(4.2, 4.2));
	checkUnit<WeakEnemyUnit, sf::CircleShape>(unit, Vector(4.2, 4.2), WEAK_ENEMY_SHAPE_COLOR, CIRCLE_WEAK_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(strong_enemy_unit){
	std::shared_ptr<EnemyUnit> unit = CircleUnitsFactory::getInstance().createStrongEnemyUnit(Vector(23, 31));
	checkUnit<StrongEnemyUnit, sf::CircleShape>(unit, Vector(23, 31), STRONG_ENEMY_SHAPE_COLOR, CIRCLE_STRONG_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(mighty_enemy_unit){
	std::shared_ptr<EnemyUnit> unit = CircleUnitsFactory::getInstance().createMightyEnemyUnit(Vector(666, 999));
	checkUnit<MightyEnemyUnit, sf::CircleShape>(unit, Vector(666, 999), MIGHTY_ENEMY_SHAPE_COLOR, CIRCLE_MIGHTY_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(hero_unit){
	std::shared_ptr<HeroUnit> unit = CircleUnitsFactory::getInstance().createHeroUnit(Vector(5, 10), std::make_shared<KeyboardController>());
	checkUnit<HeroUnit, sf::CircleShape>(unit, Vector(5, 10), HERO_SHAPE_COLOR, CIRCLE_HERO_SHAPE_SIZE);
	BOOST_CHECK(dynamic_cast<KeyboardController*>(unit->controller.get()));
}

BOOST_AUTO_TEST_CASE(shape_creating){
	std::shared_ptr<sf::Shape> shape = TestingModule::callCreateUnitShapeFromCircleUnitsFactory(100, sf::Color::Black);
	BOOST_CHECK(dynamic_cast<sf::CircleShape*>(shape.get()));
	BOOST_CHECK(shape->getFillColor() == sf::Color::Black);
	BOOST_CHECK_CLOSE_FRACTION(shape->getLocalBounds().width / 100, 1, eps2);
	BOOST_CHECK_CLOSE_FRACTION(shape->getLocalBounds().height / 100, 1, eps2);
	BOOST_CHECK_CLOSE_FRACTION(shape->getOrigin().x, (double)100 / 2, eps9);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SQUARE_UNITS_FACTORY)

BOOST_AUTO_TEST_CASE(units_factory_pattern_singleton){
	UnitsFactory& circle_units_factory1 = SquareUnitsFactory::getInstance();
	UnitsFactory& circle_units_factory2 = SquareUnitsFactory::getInstance();
	BOOST_REQUIRE_EQUAL(&circle_units_factory1, &circle_units_factory2);
}

BOOST_AUTO_TEST_CASE(weak_enemy_unit){
	std::shared_ptr<EnemyUnit> unit = SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(123, 321));
	checkUnit<WeakEnemyUnit, sf::RectangleShape>(unit, Vector(123, 321), WEAK_ENEMY_SHAPE_COLOR, SQUARE_WEAK_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(strong_enemy_unit){
	std::shared_ptr<EnemyUnit> unit = SquareUnitsFactory::getInstance().createStrongEnemyUnit(Vector(555, 111));
	checkUnit<StrongEnemyUnit, sf::RectangleShape>(unit, Vector(555, 111), STRONG_ENEMY_SHAPE_COLOR, SQUARE_STRONG_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(mighty_enemy_unit){
	std::shared_ptr<EnemyUnit> unit = SquareUnitsFactory::getInstance().createMightyEnemyUnit(Vector(77, 88));
	checkUnit<MightyEnemyUnit, sf::RectangleShape>(unit, Vector(77, 88), MIGHTY_ENEMY_SHAPE_COLOR, SQUARE_MIGHTY_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(hero_unit){
	std::shared_ptr<HeroUnit> unit = SquareUnitsFactory::getInstance().createHeroUnit(Vector(10, 5), std::make_shared<KeyboardController>());
	checkUnit<HeroUnit, sf::RectangleShape>(unit, Vector(10, 5), HERO_SHAPE_COLOR, SQUARE_HERO_SHAPE_SIZE);
	BOOST_CHECK(dynamic_cast<KeyboardController*>(unit->controller.get()));
}

BOOST_AUTO_TEST_CASE(shape_creating){
	std::shared_ptr<sf::Shape> shape = TestingModule::callCreateUnitShapeFromSquareUnitsFactory(250, sf::Color::Yellow);
	BOOST_CHECK(dynamic_cast<sf::RectangleShape*>(shape.get()));
	BOOST_CHECK(shape->getFillColor() == sf::Color::Yellow);
	BOOST_CHECK_CLOSE_FRACTION(shape->getLocalBounds().width / 250, 1, eps2);
	BOOST_CHECK_CLOSE_FRACTION(shape->getLocalBounds().height / 250, 1, eps2);
	BOOST_CHECK_CLOSE_FRACTION(shape->getOrigin().x, (double)250 / 2, eps9);
}

BOOST_AUTO_TEST_SUITE_END()