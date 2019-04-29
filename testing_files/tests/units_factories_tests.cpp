#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>
#include <memory>

#include <game_proxy.h>
#include <fake_controller.h>
#include <testing_module.h>
#include <units_factories.h>

#include <units_settings.h>

const double eps2 = 1e-2;
const double eps9 = 1e-9;

BOOST_AUTO_TEST_SUITE(UNITS_FACTORY)

template<class UnitType, class ShapeType>
void checkUnit(std::shared_ptr<Unit> unit, Vector position, double attack_cooldown,
				double attack_range, int damage, int health, sf::Color color, double shape_size){
	BOOST_CHECK_CLOSE_FRACTION(unit->getPosition().x, unit->getPosition().x, eps9);
	BOOST_CHECK_CLOSE_FRACTION(unit->getPosition().y, unit->getPosition().y, eps9);
	BOOST_CHECK_CLOSE_FRACTION(unit->getMaxAttackCooldown(), attack_cooldown, eps9);
	BOOST_CHECK_CLOSE_FRACTION(unit->getAttackRange(), attack_range, eps9);
	BOOST_CHECK_CLOSE_FRACTION((double)unit->getDamage(), damage, eps9);
	BOOST_CHECK_CLOSE_FRACTION((double)unit->getHealth(), health, eps9);
	BOOST_CHECK_CLOSE_FRACTION(unit->getShape()->getLocalBounds().width / shape_size, 1, eps2);
	BOOST_CHECK_CLOSE_FRACTION(unit->getShape()->getLocalBounds().height / shape_size, 1, eps2);
	BOOST_CHECK(std::dynamic_pointer_cast<UnitType>(unit));
	BOOST_CHECK(unit->getShape()->getFillColor() == color);
	BOOST_CHECK(std::dynamic_pointer_cast<ShapeType>(unit->getShape()));
}

void initializeGame(){
    GameProxy::initialize(CircleUnitsFactory::getInstance(), SquareUnitsFactory::getInstance(), std::make_shared<FakeController>("00000000"));
}

BOOST_AUTO_TEST_SUITE(CIRCLE_UNITS_FACTORY)

BOOST_AUTO_TEST_CASE(units_factory_pattern_singleton){
	UnitsFactory& circle_units_factory1 = CircleUnitsFactory::getInstance();
	UnitsFactory& circle_units_factory2 = CircleUnitsFactory::getInstance();
	BOOST_REQUIRE_EQUAL(&circle_units_factory1, &circle_units_factory2);
}

BOOST_AUTO_TEST_CASE(weak_enemy_unit){
	initializeGame();
	std::shared_ptr<WeakEnemyUnit> unit = CircleUnitsFactory::getInstance().createWeakEnemyUnit(Vector(4.2, 4.2));
	checkUnit<WeakEnemyUnit, sf::CircleShape>(unit,
		Vector(4.2, 4.2), CIRCLE_WEAK_ENEMY_ATTACK_COOLDOWN, WEAK_ENEMY_ATTACK_RANGE,
		CIRCLE_WEAK_ENEMY_DAMAGE, WEAK_ENEMY_HEALTH, WEAK_ENEMY_SHAPE_COLOR, CIRCLE_WEAK_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(strong_enemy_unit){
	initializeGame();
	std::shared_ptr<StrongEnemyUnit> unit = CircleUnitsFactory::getInstance().createStrongEnemyUnit(Vector(23, 31));
	checkUnit<StrongEnemyUnit, sf::CircleShape>(unit,
		Vector(23, 31), CIRCLE_STRONG_ENEMY_ATTACK_COOLDOWN, STRONG_ENEMY_ATTACK_RANGE,
		CIRCLE_STRONG_ENEMY_DAMAGE, STRONG_ENEMY_HEALTH, STRONG_ENEMY_SHAPE_COLOR, CIRCLE_STRONG_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(mighty_enemy_unit){
	initializeGame();
	std::shared_ptr<MightyEnemyUnit> unit = CircleUnitsFactory::getInstance().createMightyEnemyUnit(Vector(666, 999));
	checkUnit<MightyEnemyUnit, sf::CircleShape>(unit,
		Vector(666, 999), CIRCLE_MIGHTY_ENEMY_ATTACK_COOLDOWN, MIGHTY_ENEMY_ATTACK_RANGE,
		CIRCLE_MIGHTY_ENEMY_DAMAGE, MIGHTY_ENEMY_HEALTH, MIGHTY_ENEMY_SHAPE_COLOR, CIRCLE_MIGHTY_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(hero_unit){
	std::shared_ptr<HeroUnit> unit = CircleUnitsFactory::getInstance().createHeroUnit(Vector(5, 10), std::make_shared<KeyboardController>());
	checkUnit<HeroUnit, sf::CircleShape>(unit,
		Vector(5, 10), CIRCLE_HERO_ATTACK_COOLDOWN, HERO_ATTACK_RANGE,
		CIRCLE_HERO_DAMAGE, HERO_HEALTH, HERO_SHAPE_COLOR, CIRCLE_HERO_SHAPE_SIZE);
	BOOST_CHECK(std::dynamic_pointer_cast<KeyboardController>(unit->getController()));
}

BOOST_AUTO_TEST_CASE(shape_creating){
	std::shared_ptr<sf::Shape> shape = TestingModule::createCircleUnitShape(CircleUnitsFactory::getInstance(), 100, sf::Color::Black);
	BOOST_CHECK(std::dynamic_pointer_cast<sf::CircleShape>(shape));
	BOOST_CHECK(shape->getFillColor() == sf::Color::Black);
	BOOST_CHECK_CLOSE_FRACTION(shape->getLocalBounds().width / 100, 1, eps2);
	BOOST_CHECK_CLOSE_FRACTION(shape->getLocalBounds().height / 100, 1, eps2);
	BOOST_CHECK_CLOSE_FRACTION(shape->getOrigin().x, (double)100 / 2, eps9);
	BOOST_CHECK_CLOSE_FRACTION(shape->getOrigin().y, (double)100 / 2, eps9);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SQUARE_UNITS_FACTORY)

BOOST_AUTO_TEST_CASE(units_factory_pattern_singleton){
	UnitsFactory& circle_units_factory1 = SquareUnitsFactory::getInstance();
	UnitsFactory& circle_units_factory2 = SquareUnitsFactory::getInstance();
	BOOST_REQUIRE_EQUAL(&circle_units_factory1, &circle_units_factory2);
}

BOOST_AUTO_TEST_CASE(weak_enemy_unit){
	initializeGame();
	std::shared_ptr<WeakEnemyUnit> unit = SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(32, 12));
	checkUnit<WeakEnemyUnit, sf::RectangleShape>(unit,
		Vector(32, 12), SQUARE_WEAK_ENEMY_ATTACK_COOLDOWN, WEAK_ENEMY_ATTACK_RANGE,
		SQUARE_WEAK_ENEMY_DAMAGE, WEAK_ENEMY_HEALTH, WEAK_ENEMY_SHAPE_COLOR, SQUARE_WEAK_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(strong_enemy_unit){
	initializeGame();
	std::shared_ptr<StrongEnemyUnit> unit = SquareUnitsFactory::getInstance().createStrongEnemyUnit(Vector(88, 99));
	checkUnit<StrongEnemyUnit, sf::RectangleShape>(unit,
		Vector(88, 99), SQUARE_STRONG_ENEMY_ATTACK_COOLDOWN, STRONG_ENEMY_ATTACK_RANGE,
		SQUARE_STRONG_ENEMY_DAMAGE, STRONG_ENEMY_HEALTH, STRONG_ENEMY_SHAPE_COLOR, SQUARE_STRONG_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(mighty_enemy_unit){
	initializeGame();
	std::shared_ptr<MightyEnemyUnit> unit = SquareUnitsFactory::getInstance().createMightyEnemyUnit(Vector(1.1, 7.7));
	checkUnit<MightyEnemyUnit, sf::RectangleShape>(unit,
		Vector(1.1, 7.7), SQUARE_MIGHTY_ENEMY_ATTACK_COOLDOWN, MIGHTY_ENEMY_ATTACK_RANGE,
		SQUARE_MIGHTY_ENEMY_DAMAGE, MIGHTY_ENEMY_HEALTH, MIGHTY_ENEMY_SHAPE_COLOR, SQUARE_MIGHTY_ENEMY_SHAPE_SIZE);
}

BOOST_AUTO_TEST_CASE(hero_unit){
	std::shared_ptr<HeroUnit> unit = SquareUnitsFactory::getInstance().createHeroUnit(Vector(10, 5), std::make_shared<KeyboardController>());
	checkUnit<HeroUnit, sf::RectangleShape>(unit,
		Vector(10, 5), SQUARE_HERO_ATTACK_COOLDOWN, HERO_ATTACK_RANGE,
		SQUARE_HERO_DAMAGE, HERO_HEALTH, HERO_SHAPE_COLOR, SQUARE_HERO_SHAPE_SIZE);
	BOOST_CHECK(std::dynamic_pointer_cast<KeyboardController>(unit->getController()));
}

BOOST_AUTO_TEST_CASE(shape_creating){
	std::shared_ptr<sf::Shape> shape = TestingModule::createCircleUnitShape(SquareUnitsFactory::getInstance(), 250, sf::Color::Yellow);
	BOOST_CHECK(std::dynamic_pointer_cast<sf::RectangleShape>(shape));
	BOOST_CHECK(shape->getFillColor() == sf::Color::Yellow);
	BOOST_CHECK_CLOSE_FRACTION(shape->getLocalBounds().width / 250, 1, eps2);
	BOOST_CHECK_CLOSE_FRACTION(shape->getLocalBounds().height / 250, 1, eps2);
	BOOST_CHECK_CLOSE_FRACTION(shape->getOrigin().x, (double)250 / 2, eps9);
	BOOST_CHECK_CLOSE_FRACTION(shape->getOrigin().y, (double)250 / 2, eps9);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()