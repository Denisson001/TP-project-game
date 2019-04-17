#include <boost/test/unit_test.hpp>

#include <game_proxy.h>
#include <enemy_units_booster.h>
#include <testing_module.h>

#include <units_settings.h>

const double eps9 = 1e-9;

BOOST_AUTO_TEST_SUITE(ENEMY_UNITS_BOOSTER)

BOOST_AUTO_TEST_CASE(update_method){
    GameProxy::initialize(CircleUnitsFactory::getInstance(), SquareUnitsFactory::getInstance());
    std::vector<std::shared_ptr<EnemyUnit>> enemy_units;
    for (int i = 0; i < 5; i++){
        enemy_units.push_back(SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)));
        EnemyUnitsBooster::addEnemyUnit(enemy_units.back());
    }
    enemy_units[2]->getHealth() = 0;
    EnemyUnitsBooster::update();
    BOOST_CHECK((int)TestingModule::getEnemyUnitsAmountFromEnemyUnitsBooster() == 4);
    for (int i = 0; i < 5; i++) if (i != 2){
        int correct_health;
        if (i < 2){
            correct_health = WEAK_ENEMY_HEALTH + WEAK_ENEMY_ADDITIONAL_HEALTH;
        } else {
            correct_health = WEAK_ENEMY_HEALTH;
        }
        correct_health = std::min(correct_health, WEAK_ENEMY_MAX_HEALTH);
        BOOST_CHECK(enemy_units[i]->getHealth() == correct_health);
    }
}

BOOST_AUTO_TEST_SUITE_END()
