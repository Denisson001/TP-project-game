#include <boost/test/unit_test.hpp>

#include <game_proxy.h>
#include <hero_unit_attack_module.h>
#include <fake_controller.h>
#include <testing_module.h>

#include <units_settings.h>
#include <math_settings.h>

BOOST_AUTO_TEST_SUITE(HERO_UNIT_ATTACK_MODULE)

std::shared_ptr<Game> initializeGame(std::string controller_string){
    GameProxy::initialize(CircleUnitsFactory::getInstance(), SquareUnitsFactory::getInstance(), std::make_shared<FakeController>(controller_string));
    return GameProxy::getGameInstance();
}

BOOST_AUTO_TEST_CASE(getDirectionFromController_method){
    std::shared_ptr<HeroUnitAttackModule> attack_modules[3] = {std::make_shared<SingleShotModule>(),
                                                               std::make_shared<SplitShotModule>(),
                                                               std::make_shared<TripleShotModule>()};
    for (int mask = 0; mask < (1 << 4); mask++){
        std::string controller_string = "0000";
        for (int i = 0; i < 4; i++){
            controller_string += '0' + ((mask >> i) & 1);
        }
        std::shared_ptr<Controller> controller = std::make_shared<FakeController>(controller_string);
        for (int attack_module_number = 0; attack_module_number < 3; attack_module_number++){
            std::pair<int, int> direction = TestingModule::getDirectionFromController(attack_modules[attack_module_number], controller);
            int dx = ((mask >> 3) & 1) - ((mask >> 2) & 1);
            int dy = ((mask >> 1) & 1) - ((mask >> 0) & 1);
            BOOST_CHECK(dx == direction.first);
            BOOST_CHECK(dy == direction.second);
        }
    }
}

template<class AttackModuleType>
void checkBulletsSettings(int bullets_amount){
    for (int mask = 0; mask < (1 << 4); mask++){
        std::string controller_string = "0000";
        for (int i = 0; i < 4; i++){
            controller_string += '0' + ((mask >> i) & 1);
        }
        int dx = ((mask >> 3) & 1) - ((mask >> 2) & 1);
        int dy = ((mask >> 1) & 1) - ((mask >> 0) & 1);
        std::shared_ptr<Game> game = initializeGame(controller_string);
        std::shared_ptr<HeroUnitAttackModule> attack_module = std::make_shared<AttackModuleType>();
        attack_module->initialize();
        attack_module->update(0, TestingModule::getHeroUnit(game).get());
        std::vector<std::shared_ptr<Bullet>>& bullets = TestingModule::getHeroUnitBullets(game);
        if (abs(dx) + abs(dy) == 0){
            BOOST_CHECK((int)bullets.size() == 0);
        } else {
            BOOST_CHECK((int)bullets.size() == bullets_amount);
            int v = bullets_amount / 2;
            for (int i = -v; i <= v; i++){
                Vector vector = Vector(dx, dy).resize(BULLET_SPEED).rotate(BULLET_DEFLECTION_ANGLE * i);
                BOOST_CHECK_CLOSE_FRACTION(vector.x, bullets[i + v]->vector.x, eps9);
                BOOST_CHECK_CLOSE_FRACTION(vector.y, bullets[i + v]->vector.y, eps9);
            }
        }
    }
}

void checkBulletsAmount(std::shared_ptr<HeroUnitAttackModule> attack_module, int bullets_amount){
    std::shared_ptr<Game> game = initializeGame("00001010");
    std::shared_ptr<HeroUnit> hero_unit = TestingModule::getHeroUnit(game);
    attack_module->initialize();
    attack_module->update(0, hero_unit.get());
    BOOST_CHECK((int)TestingModule::getHeroUnitBullets(game).size() == bullets_amount);
    attack_module->update(hero_unit->getMaxAttackCooldown() + eps9, hero_unit.get());
    BOOST_CHECK((int)TestingModule::getHeroUnitBullets(game).size() == 2 * bullets_amount);
    if (hero_unit->getMaxAttackCooldown() >= eps9){
        attack_module->update(hero_unit->getMaxAttackCooldown() / 2, hero_unit.get());
        BOOST_CHECK((int)TestingModule::getHeroUnitBullets(game).size() == 2 * bullets_amount);
    }
}

BOOST_AUTO_TEST_SUITE(SINGLE_SHOT_MODULE)

BOOST_AUTO_TEST_CASE(update_method_bullets_settings){
    checkBulletsSettings<SingleShotModule>(1);
}
    
BOOST_AUTO_TEST_CASE(update_method_bullets_amount){
    checkBulletsAmount(std::make_shared<SingleShotModule>(), 1);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SPLIT_SHOT_MODULE)

BOOST_AUTO_TEST_CASE(update_method_bullets_settings){
    checkBulletsSettings<SplitShotModule>(3);
}

BOOST_AUTO_TEST_CASE(update_method_bullets_amount){
    checkBulletsAmount(std::make_shared<SplitShotModule>(), 3);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TRIPLE_SHOT_MODULE)

BOOST_AUTO_TEST_CASE(update_method_bullets_settings){
    checkBulletsSettings<TripleShotModule>(1);
}

BOOST_AUTO_TEST_CASE(update_method_bullets_amount){
    std::shared_ptr<Game> game = initializeGame("00001010");
    std::shared_ptr<HeroUnit> hero_unit = TestingModule::getHeroUnit(game);
    std::shared_ptr<HeroUnitAttackModule> attack_module = std::make_shared<TripleShotModule>();
    attack_module->initialize();
    attack_module->update(eps9, hero_unit.get());
    for (int i = 0; i < 3; i++){
        BOOST_CHECK((int)TestingModule::getHeroUnitBullets(game).size() == i + 1);
        if (i + 1 != 3){
            attack_module->update(HERO_MINI_ATTACK_COOLDOWN + eps9, hero_unit.get());
        }
    }
    if (hero_unit->getMaxAttackCooldown() >= eps9){
        attack_module->update(hero_unit->getMaxAttackCooldown() / 2, hero_unit.get());
        BOOST_CHECK((int)TestingModule::getHeroUnitBullets(game).size() == 3);
        attack_module->update(hero_unit->getMaxAttackCooldown() / 2 + eps9, hero_unit.get());
        BOOST_CHECK((int)TestingModule::getHeroUnitBullets(game).size() == 4);
    }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
