#include <boost/test/unit_test.hpp>

#include <memory>

#include <testing_module.h>
#include <game_proxy.h>
#include <fake_controller.h>

#include <units_settings.h>
#include <game_settings.h>
#include <math_settings.h>

BOOST_AUTO_TEST_SUITE(GAME_MODULE)

std::shared_ptr<Game> initializeGame(){
    GameProxy::initialize(CircleUnitsFactory::getInstance(), SquareUnitsFactory::getInstance(), std::make_shared<FakeController>("10000000"));
    return TestingModule::getGameInstance();
}

BOOST_AUTO_TEST_CASE(getRandomFreeGridCell_method){
    std::shared_ptr<Game> game = initializeGame();
    TestingModule::getHeroUnit(game)->getPosition() = Vector(-1e9, -1e9);

    for (int it = 0; it < HORIZONTAL_DOTS_AMOUNT * VERTICAL_DOTS_AMOUNT; it++){
        std::pair<int, int> free_cell = TestingModule::getRandomFreeGridCell(game);
        BOOST_CHECK(free_cell != std::make_pair(-1, -1));
        BOOST_CHECK(GameProxy::getGridCellValue(free_cell) == 0);
        GameProxy::setGridCellValue(free_cell, 1);
    }
    
    std::pair<int, int> free_cell = TestingModule::getRandomFreeGridCell(game);
    BOOST_CHECK(free_cell == std::make_pair(-1, -1));

    GameProxy::setGridCellValue(std::make_pair(1, 1), 0);
    free_cell = TestingModule::getRandomFreeGridCell(game);
    BOOST_CHECK(free_cell == std::make_pair(1, 1));

    TestingModule::getHeroUnit(game)->getPosition() = Vector(HORIZONTAL_GAP_SIZE, VERITCAL_GAP_SIZE);

    free_cell = TestingModule::getRandomFreeGridCell(game);
    BOOST_CHECK(free_cell == std::make_pair(-1, -1));
}

BOOST_AUTO_TEST_CASE(updateEnemyUnitsBullets_method){
    std::shared_ptr<Game> game = initializeGame();
    std::shared_ptr<HeroUnit> hero_unit = TestingModule::getHeroUnit(game);

    Vector direction(1, 0),
           shift_x = Vector(HERO_SHAPE_MAX_SIZE + ENEMY_SHAPE_MAX_SIZE, 0),
           shift_y = Vector(HERO_SHAPE_MAX_SIZE + ENEMY_SHAPE_MAX_SIZE, 0),
           position1 = hero_unit->getPosition() - shift_x,
           position2 = hero_unit->getPosition() - shift_x + shift_y,
           position3 = hero_unit->getPosition() - shift_x - shift_y;

    std::shared_ptr<EnemyUnit> enemy_units[3] = {CircleUnitsFactory::getInstance().createWeakEnemyUnit(position1),
                                                 CircleUnitsFactory::getInstance().createStrongEnemyUnit(position2),
                                                 SquareUnitsFactory::getInstance().createMightyEnemyUnit(position3)};

    for (int i = 0; i < 3; i++){
        TestingModule::addBullet(enemy_units[i], direction);
    }

    double time = (hero_unit->getPosition() - enemy_units[0]->getPosition()).length() / BULLET_SPEED;
    double old_health = hero_unit->getHealth();
    TestingModule::updateEnemyUnitsBullets(game, time);
    double new_health = hero_unit->getHealth();

    BOOST_CHECK(old_health != new_health);
}

BOOST_AUTO_TEST_CASE(updateHeroUnitBullets_method){
    std::shared_ptr<Game> game = initializeGame();
    std::shared_ptr<HeroUnit> hero_unit = TestingModule::getHeroUnit(game);

    Vector direction(-1, 0),
           shift_x = Vector(HERO_SHAPE_MAX_SIZE + ENEMY_SHAPE_MAX_SIZE, 0),
           position = hero_unit->getPosition() - shift_x;

    std::shared_ptr<EnemyUnit> enemy_unit = CircleUnitsFactory::getInstance().createWeakEnemyUnit(position);
    TestingModule::getEnemyUnits(game).push_back(enemy_unit);
    TestingModule::addBullet(hero_unit, direction);

    double time = (hero_unit->getPosition() - position).length() / BULLET_SPEED;
    double old_health = enemy_unit->getHealth();

    TestingModule::updateHeroUnitBullets(game, time);

    if ((int)TestingModule::getEnemyUnits(game).size() != 0){
        double new_health = enemy_unit->getHealth();
        BOOST_CHECK(old_health != new_health);
    }
}

BOOST_AUTO_TEST_CASE(eraseFromVector_method){
    std::shared_ptr<Game> game = initializeGame();
    std::shared_ptr<EnemyUnit> enemy_unit1 = CircleUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)), 
                               enemy_unit2 = CircleUnitsFactory::getInstance().createStrongEnemyUnit(Vector(0, 0)), 
                               enemy_unit3 = CircleUnitsFactory::getInstance().createMightyEnemyUnit(Vector(0, 0)), 
                               enemy_unit4 = SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)); 
    std::vector<std::shared_ptr<EnemyUnit>> vector = {enemy_unit1, enemy_unit2, enemy_unit3, enemy_unit4};
    int i = 2;
    TestingModule::eraseFromVector(game, vector, i);
    BOOST_CHECK(i == 1);
    BOOST_CHECK((int)vector.size() == 3);
    BOOST_CHECK(vector[0] == enemy_unit1);
    BOOST_CHECK(vector[1] == enemy_unit2);
    BOOST_CHECK(vector[2] == enemy_unit4);
}   

BOOST_AUTO_TEST_CASE(initialize_method){
    std::shared_ptr<Game> game = initializeGame();
    
    game->timer = 50;
    game->killed_enemy_units_amount = 100;
    GameProxy::setGridCellValue(std::make_pair(1, 1), 1);
    
    std::shared_ptr<Controller> controller = std::make_shared<FakeController>("00000000");
    game->initialize(SquareUnitsFactory::getInstance(), controller);

    BOOST_CHECK(game->timer == 0);
    BOOST_CHECK(game->killed_enemy_units_amount == 0);

    for (int i = 1; i <= HORIZONTAL_DOTS_AMOUNT; i++){
        for (int j = 1; j <= VERTICAL_DOTS_AMOUNT; j++){
            BOOST_CHECK(GameProxy::getGridCellValue(std::make_pair(i, j)) == 0);
        }
    }

    std::shared_ptr<HeroUnit> hero_unit = TestingModule::getHeroUnit(game);

    BOOST_CHECK(hero_unit->getController() == controller);
    BOOST_CHECK_CLOSE_FRACTION(hero_unit->getPosition().x, WINDOW_WIDTH / 2, eps9);
    BOOST_CHECK_CLOSE_FRACTION(hero_unit->getPosition().y, WINDOW_HEIGHT / 2, eps9);
}

BOOST_AUTO_TEST_CASE(update_method){
    std::shared_ptr<Game> game = initializeGame();

    std::shared_ptr<EnemyUnit> enemy_unit = CircleUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0));
    TestingModule::getEnemyUnits(game).push_back(enemy_unit);
    
    double time = 50;
    Vector old_position = TestingModule::getHeroUnit(game)->getPosition();

    game->update(time);

    Vector new_position = TestingModule::getHeroUnit(game)->getPosition();

    BOOST_CHECK_CLOSE_FRACTION(game->timer, time, eps9);
    BOOST_CHECK_CLOSE_FRACTION((old_position - new_position).length(), HERO_MOVESPEED * time,  eps9);
    BOOST_CHECK_CLOSE_FRACTION(enemy_unit->getCurrentAttackCooldown() + time, enemy_unit->getMaxAttackCooldown(), eps9);
}

BOOST_AUTO_TEST_CASE(spawnEnemyUnits_method){
    std::shared_ptr<Game> game = initializeGame();
    for (int i = 0; i < MIN_ENEMY_UNITS_AMOUNT; i++){
        game->update(ENEMY_UNITS_SMALL_SPAWN_GAP / 2);
        BOOST_CHECK((int)TestingModule::getEnemyUnits(game).size() == i);
        game->update(ENEMY_UNITS_SMALL_SPAWN_GAP / 2 + eps9);
        BOOST_CHECK((int)TestingModule::getEnemyUnits(game).size() == i + 1);
    }
    for (int i = 0; i < MAX_ENEMY_UNITS_AMOUNT - MIN_ENEMY_UNITS_AMOUNT; i++){
        game->update(ENEMY_UNITS_BIG_SPAWN_GAP / 2);
        BOOST_CHECK((int)TestingModule::getEnemyUnits(game).size() == MIN_ENEMY_UNITS_AMOUNT + i);
        game->update(ENEMY_UNITS_BIG_SPAWN_GAP / 2 + eps9);
        BOOST_CHECK((int)TestingModule::getEnemyUnits(game).size() == MIN_ENEMY_UNITS_AMOUNT + i + 1);
    }
}

BOOST_AUTO_TEST_SUITE_END()
