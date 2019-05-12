#include <boost/test/unit_test.hpp>

#include <memory>

#include <controller.h>
#include <geometry.h>
#include <units_factories.h>
#include <testing_module.h>
#include <game_proxy.h>
#include <fake_controller.h>

#include <math_settings.h>
#include <units_settings.h>

BOOST_AUTO_TEST_SUITE(UNITS_UNIT)

std::shared_ptr<Game> initializeGame(std::string controller_string){
    GameProxy::initialize(CircleUnitsFactory::getInstance(), SquareUnitsFactory::getInstance(), std::make_shared<FakeController>(controller_string));
    return TestingModule::getGameInstance();
}

BOOST_AUTO_TEST_CASE(get_methods){
    Vector position = Vector(0, 0);
    std::shared_ptr<Unit> unit = CircleUnitsFactory::getInstance().createHeroUnit(position, std::make_shared<KeyboardController>());
    BOOST_CHECK_CLOSE_FRACTION(unit->getPosition().x, position.x, eps9);
    BOOST_CHECK_CLOSE_FRACTION(unit->getPosition().y, position.y, eps9);
    BOOST_CHECK(std::dynamic_pointer_cast<sf::CircleShape>(unit->getShape()) != nullptr);
    BOOST_CHECK(std::dynamic_pointer_cast<sf::RectangleShape>(unit->getShape()) == nullptr);
    BOOST_CHECK_CLOSE_FRACTION(unit->getAttackRange(), HERO_ATTACK_RANGE, eps9);
    BOOST_CHECK(unit->getDamage() == CIRCLE_HERO_DAMAGE);
    BOOST_CHECK(unit->getHealth() == HERO_HEALTH);
    BOOST_CHECK_CLOSE_FRACTION(unit->getMaxAttackCooldown(), CIRCLE_HERO_ATTACK_COOLDOWN, eps9);
}

BOOST_AUTO_TEST_CASE(getBounds_method){
    for (int x = 0; x <= 1000; x += 10){
        for (int y = 0; y <= 1000; y += 10){
            Vector position = Vector(x, y);
            std::shared_ptr<Unit> unit = CircleUnitsFactory::getInstance().createHeroUnit(position, std::make_shared<KeyboardController>());
            sf::FloatRect unit_bounds = unit->getBounds();
            BOOST_CHECK(unit_bounds.left <= position.x);
            BOOST_CHECK(unit_bounds.top <= position.y);
            BOOST_CHECK(unit_bounds.left + unit_bounds.width >= position.x);
            BOOST_CHECK(unit_bounds.top + unit_bounds.height >= position.y);
        }
    }
}

BOOST_AUTO_TEST_CASE(update_method){
    std::shared_ptr<Game> game = initializeGame("10101010");
    std::shared_ptr<Unit> unit = TestingModule::getHeroUnit(game);
    double time = unit->getMaxAttackCooldown() + eps9;
    Vector old_position = unit->getPosition();
    unit->update(time);
    Vector new_position = unit->getPosition();
    BOOST_CHECK((int)TestingModule::getHeroUnitBullets(game).size() > 0);
    BOOST_CHECK_CLOSE_FRACTION((new_position - old_position).length(), HERO_MOVESPEED * time, eps9);
}

BOOST_AUTO_TEST_SUITE_END()