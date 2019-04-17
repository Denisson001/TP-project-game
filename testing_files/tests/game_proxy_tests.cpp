#include <boost/test/unit_test.hpp>

#include <testing_module.h>
#include <game_proxy.h>

#include <units_settings.h>

const double eps9 = 1e-9;

BOOST_AUTO_TEST_SUITE(GAME_PROXY)

std::shared_ptr<Game> initializeGame(){
    GameProxy::initialize(CircleUnitsFactory::getInstance(), SquareUnitsFactory::getInstance());
    return GameProxy::getGameInstance();
}

BOOST_AUTO_TEST_CASE(getHeroUnitPosition_method){
    std::shared_ptr<Game> game = initializeGame();
    BOOST_CHECK_CLOSE_FRACTION(GameProxy::getHeroUnitPosition().x,
        TestingModule::getHeroUnitFromGame(game)->getPosition().x, eps9);
    BOOST_CHECK_CLOSE_FRACTION(GameProxy::getHeroUnitPosition().y,
        TestingModule::getHeroUnitFromGame(game)->getPosition().y, eps9);
}

BOOST_AUTO_TEST_CASE(addEnemyUnitBullet_method){
    std::shared_ptr<Game> game = initializeGame();
    GameProxy::addEnemyUnitBullet(std::make_shared<Bullet>());
    BOOST_CHECK((int)TestingModule::getEnemyUnitsBulletsFromGame(game).size() == 1);
}

BOOST_AUTO_TEST_CASE(addHeroUnitBullet_method){
    std::shared_ptr<Game> game = initializeGame();
    GameProxy::addHeroUnitBullet(std::make_shared<Bullet>());
    BOOST_CHECK((int)TestingModule::getHeroUnitBulletsFromGame(game).size() == 1);
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
    TestingModule::getEnemyUnitsFromGame(game).push_back(SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(GameProxy::getHeroUnitPosition())));
    BOOST_CHECK(GameProxy::checkHeroUnitPosition() == 0);
    TestingModule::getEnemyUnitsFromGame(game).clear();
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

BOOST_AUTO_TEST_SUITE_END()
