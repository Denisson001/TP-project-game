#include <boost/test/unit_test.hpp>

#include <testing_module.h>
#include <game_proxy.h>
#include <fake_controller.h>

#include <units_settings.h>

const double eps9 = 1e-9;

BOOST_AUTO_TEST_SUITE(GAME_PROXY)

std::shared_ptr<Game> initializeGame(){
    GameProxy::initialize(CircleUnitsFactory::getInstance(), SquareUnitsFactory::getInstance(), std::make_shared<FakeController>("00000000"));
    return GameProxy::getGameInstance();
}

BOOST_AUTO_TEST_CASE(getGameInstance_method){
    std::shared_ptr<Game> game = initializeGame();
    BOOST_CHECK(game != nullptr);
}

BOOST_AUTO_TEST_CASE(getHeroUnitPosition_method){
    std::shared_ptr<Game> game = initializeGame();
    BOOST_CHECK_CLOSE_FRACTION(GameProxy::getHeroUnitPosition().x, TestingModule::getHeroUnit(game)->getPosition().x, eps9);
    BOOST_CHECK_CLOSE_FRACTION(GameProxy::getHeroUnitPosition().y, TestingModule::getHeroUnit(game)->getPosition().y, eps9);
}

BOOST_AUTO_TEST_CASE(addEnemyUnitBullet_method){
    std::shared_ptr<Game> game = initializeGame();
    GameProxy::addEnemyUnitBullet(std::make_shared<Bullet>());
    BOOST_CHECK((int)TestingModule::getEnemyUnitsBullets(game).size() == 1);
}

BOOST_AUTO_TEST_CASE(addHeroUnitBullet_method){
    std::shared_ptr<Game> game = initializeGame();
    GameProxy::addHeroUnitBullet(std::make_shared<Bullet>());
    BOOST_CHECK((int)TestingModule::getHeroUnitBullets(game).size() == 1);
}

BOOST_AUTO_TEST_CASE(setGridCellValue_getGridCellValue_methods){
    std::shared_ptr<Game> game = initializeGame();
    GameProxy::setGridCellValue(std::make_pair(1, 1), 1);
    BOOST_CHECK(GameProxy::getGridCellValue(std::make_pair(1, 1)) == 1);
    GameProxy::setGridCellValue(std::make_pair(1, 1), 0);
    BOOST_CHECK(GameProxy::getGridCellValue(std::make_pair(1, 1)) == 0);
}

BOOST_AUTO_TEST_CASE(checkHeroUnitPosition_method){
    std::shared_ptr<Game> game = initializeGame();
    BOOST_CHECK(GameProxy::checkHeroUnitPosition() == 1);
    TestingModule::getEnemyUnits(game).push_back(SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(GameProxy::getHeroUnitPosition())));
    BOOST_CHECK(GameProxy::checkHeroUnitPosition() == 0);
    TestingModule::getEnemyUnits(game).clear();
}

BOOST_AUTO_TEST_CASE(checkEnemyUnitPosition_method){
    std::shared_ptr<Game> game = initializeGame();
    Vector enemy_unit_position = GameProxy::getHeroUnitPosition();
    std::shared_ptr<EnemyUnit> enemy_unit = SquareUnitsFactory::getInstance().createWeakEnemyUnit(enemy_unit_position);
    BOOST_CHECK(GameProxy::checkEnemyUnitPosition(enemy_unit->getBounds()) == 0);
    enemy_unit_position += Vector(ENEMY_SHAPE_MAX_SIZE, ENEMY_SHAPE_MAX_SIZE);
    enemy_unit_position += Vector(HERO_SHAPE_MAX_SIZE, HERO_SHAPE_MAX_SIZE);
    enemy_unit = SquareUnitsFactory::getInstance().createWeakEnemyUnit(enemy_unit_position);
    BOOST_CHECK(GameProxy::checkEnemyUnitPosition(enemy_unit->getBounds()) == 1);
}

BOOST_AUTO_TEST_CASE(getTime_method){
    std::shared_ptr<Game> game = initializeGame();
    game->timer = 42;
    BOOST_CHECK_CLOSE_FRACTION(42, GameProxy::getTime(), eps9);
}


BOOST_AUTO_TEST_CASE(getKilledEnemyUnitsAmount_method){
    std::shared_ptr<Game> game = initializeGame();
    game->killed_enemy_units_amount = 42;
    BOOST_CHECK(42 == GameProxy::getKilledEnemyUnitsAmount());
}

BOOST_AUTO_TEST_SUITE_END()
