#include <boost/test/unit_test.hpp>

#include <game_proxy.h>
#include <fake_controller.h>
#include <enemy_units_decorators.h>
#include <testing_module.h>

#include <units_settings.h>
#include <game_settings.h>
#include <math_settings.h>

BOOST_AUTO_TEST_SUITE(ENEMY_UNITS_DECORATORS)

std::shared_ptr<Game> initializeGame(){
    GameProxy::initialize(CircleUnitsFactory::getInstance(), SquareUnitsFactory::getInstance(), std::make_shared<FakeController>("00000000"));
    return TestingModule::getGameInstance();
}


BOOST_AUTO_TEST_SUITE(ENEMY_UNIT_DECORATOR)

void checkGetMethods(std::shared_ptr<EnemyUnit> enemy_unit, std::shared_ptr<EnemyUnit> decorated_enemy_unit){
    BOOST_CHECK_CLOSE_FRACTION(enemy_unit->getPosition().x, decorated_enemy_unit->getPosition().x, eps9);
    BOOST_CHECK_CLOSE_FRACTION(enemy_unit->getPosition().y, decorated_enemy_unit->getPosition().y, eps9);
    BOOST_CHECK_CLOSE_FRACTION(enemy_unit->getMaxAttackCooldown(), decorated_enemy_unit->getMaxAttackCooldown(), eps9);
    BOOST_CHECK_CLOSE_FRACTION(enemy_unit->getCurrentAttackCooldown(), decorated_enemy_unit->getCurrentAttackCooldown(), eps9);
    BOOST_CHECK_CLOSE_FRACTION(enemy_unit->getAttackRange(), decorated_enemy_unit->getAttackRange(), eps9);
    BOOST_CHECK(enemy_unit->getDamage() == decorated_enemy_unit->getDamage());
    BOOST_CHECK(enemy_unit->getHealth() == decorated_enemy_unit->getHealth());
    BOOST_CHECK(enemy_unit->getCurrentGridPosition() == decorated_enemy_unit->getCurrentGridPosition());
}

BOOST_AUTO_TEST_CASE(get_methods){
    initializeGame();
    std::shared_ptr<EnemyUnit> enemy_units[6] = {CircleUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)),
                                                 SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)),
                                                 CircleUnitsFactory::getInstance().createStrongEnemyUnit(Vector(0, 0)),
                                                 SquareUnitsFactory::getInstance().createStrongEnemyUnit(Vector(0, 0)),
                                                 CircleUnitsFactory::getInstance().createMightyEnemyUnit(Vector(0, 0)),
                                                 SquareUnitsFactory::getInstance().createMightyEnemyUnit(Vector(0, 0))};
    for (int i = 0; i < 6; i++){
        std::shared_ptr<EnemyUnit> decorated_enemy_unit1 = std::make_shared<EnemySuperAttackDecorator>(enemy_units[i]);
        std::shared_ptr<EnemyUnit> decorated_enemy_unit2 = std::make_shared<EnemyMovementDecorator>(enemy_units[i]);
        checkGetMethods(enemy_units[i], decorated_enemy_unit1);
        checkGetMethods(enemy_units[i], decorated_enemy_unit2);
        checkGetMethods(enemy_units[i], std::make_shared<EnemySuperAttackDecorator>(decorated_enemy_unit2));
        checkGetMethods(enemy_units[i], std::make_shared<EnemyMovementDecorator>(decorated_enemy_unit1));
    }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ENEMY_SUPER_ATTACK_DECORATOR)

void checkBulletsSettings(std::shared_ptr<EnemyUnit> enemy_unit, int bullets_amount){
    std::shared_ptr<Game> game = initializeGame();
    TestingModule::updateAttackModule(enemy_unit, enemy_unit->getMaxAttackCooldown() * SUPER_ATTACK_ADDITIONAL_ATTACK_COOLDOWN_COEFFICIENT + eps9);
    std::vector<std::shared_ptr<Bullet>>& bullets = TestingModule::getEnemyUnitsBullets(game);
    BOOST_CHECK((int)bullets.size() == bullets_amount);
    Vector direction = TestingModule::getHeroUnit(game)->getPosition() - enemy_unit->getPosition();
    for (int i = 0; i < bullets_amount; i++){
        Vector vector = direction.resize(BULLET_SPEED).rotate(2 * PI * i / SUPER_ATTACK_BULLETS_AMOUNT);
        BOOST_CHECK_CLOSE_FRACTION(vector.x, bullets[i]->vector.x, eps9);
        BOOST_CHECK_CLOSE_FRACTION(vector.y, bullets[i]->vector.y, eps9);
    }
}

void checkBulletsAmount(std::shared_ptr<EnemyUnit> enemy_unit, int bullets_amount){
    std::shared_ptr<Game> game = initializeGame();
    TestingModule::updateAttackModule(enemy_unit, enemy_unit->getMaxAttackCooldown() * SUPER_ATTACK_ADDITIONAL_ATTACK_COOLDOWN_COEFFICIENT + eps9);
    BOOST_CHECK((int)TestingModule::getEnemyUnitsBullets(game).size() == bullets_amount);
    if (enemy_unit->getMaxAttackCooldown() >= eps9){
        TestingModule::updateAttackModule(enemy_unit, enemy_unit->getMaxAttackCooldown() * SUPER_ATTACK_ADDITIONAL_ATTACK_COOLDOWN_COEFFICIENT / 2);
        BOOST_CHECK((int)TestingModule::getEnemyUnitsBullets(game).size() == bullets_amount);
        TestingModule::updateAttackModule(enemy_unit, enemy_unit->getMaxAttackCooldown() * SUPER_ATTACK_ADDITIONAL_ATTACK_COOLDOWN_COEFFICIENT / 2 + eps9);
        BOOST_CHECK((int)TestingModule::getEnemyUnitsBullets(game).size() == 2 * bullets_amount);
    }
}

BOOST_AUTO_TEST_CASE(updateAttackModule_method){
    std::shared_ptr<EnemyUnit> enemy_units[6] = {CircleUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)),
                                                 SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)),
                                                 CircleUnitsFactory::getInstance().createStrongEnemyUnit(Vector(0, 0)),
                                                 SquareUnitsFactory::getInstance().createStrongEnemyUnit(Vector(0, 0)),
                                                 CircleUnitsFactory::getInstance().createMightyEnemyUnit(Vector(0, 0)),
                                                 SquareUnitsFactory::getInstance().createMightyEnemyUnit(Vector(0, 0))};
    for (int i = 0; i < 6; i++){
        std::shared_ptr<EnemyUnit> decorated_enemy_unit = std::make_shared<EnemySuperAttackDecorator>(enemy_units[i]);
        checkBulletsAmount(decorated_enemy_unit, SUPER_ATTACK_BULLETS_AMOUNT);
        checkBulletsSettings(decorated_enemy_unit, SUPER_ATTACK_BULLETS_AMOUNT);
    }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ENEMY_MOVEMENT_DECORATOR)

BOOST_AUTO_TEST_CASE(updateAttackModule_method){
    std::shared_ptr<Game> game = initializeGame();
    std::shared_ptr<EnemyUnit> enemy_unit = CircleUnitsFactory::getInstance().createStrongEnemyUnit(Vector(0, 0));
    std::shared_ptr<EnemyUnit> decorated_enemy_unit = std::make_shared<EnemyMovementDecorator>(enemy_unit);
    TestingModule::updateAttackModule(decorated_enemy_unit, decorated_enemy_unit->getMaxAttackCooldown() + eps9);
    BOOST_CHECK((int)TestingModule::getEnemyUnitsBullets(game).size() == 3);
}

BOOST_AUTO_TEST_CASE(convertGridCellToVector_method){
    initializeGame();
    std::shared_ptr<EnemyMovementDecorator> decorated_enemy_unit = std::make_shared<EnemyMovementDecorator>(CircleUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)));
    for (int cell_x = 1; cell_x <= HORIZONTAL_DOTS_AMOUNT; cell_x++){
        for (int cell_y = 1; cell_y <= VERTICAL_DOTS_AMOUNT; cell_y++){
            Vector position = TestingModule::convertGridCellToVector(decorated_enemy_unit, std::make_pair(cell_x, cell_y));
            Vector correct_position = Vector(cell_x * HORIZONTAL_GAP_SIZE, cell_y * VERITCAL_GAP_SIZE);
            BOOST_CHECK_CLOSE_FRACTION(position.x, correct_position.x, eps9);
            BOOST_CHECK_CLOSE_FRACTION(position.y, correct_position.y, eps9);
        }
    }
}

BOOST_AUTO_TEST_CASE(updateMovementModule_method){
    initializeGame();
    std::shared_ptr<EnemyMovementDecorator> decorated_enemy_unit = 
                                std::make_shared<EnemyMovementDecorator>(SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(HORIZONTAL_GAP_SIZE, VERITCAL_GAP_SIZE)));
    double time = 50;
    for (int i = 0; i < 10000; i++){
        Vector old_position = decorated_enemy_unit->getPosition();
        TestingModule::updateMovementModule(decorated_enemy_unit, time);
        Vector new_position = decorated_enemy_unit->getPosition();
        BOOST_CHECK((old_position - new_position).length() <= ENEMY_MOVESPEED * time);
        BOOST_CHECK(new_position.x >= -eps9);
        BOOST_CHECK(new_position.y >= -eps9);
        BOOST_CHECK(new_position.x <= WINDOW_WIDTH + eps9);
        BOOST_CHECK(new_position.y <= WINDOW_HEIGHT + eps9);
    }
}

BOOST_AUTO_TEST_CASE(setNewGridPosition_method){
    initializeGame();
    std::shared_ptr<EnemyMovementDecorator> decorated_enemy_unit = std::make_shared<EnemyMovementDecorator>(SquareUnitsFactory::getInstance().createWeakEnemyUnit(Vector(0, 0)));
    for (int i = 1; i <= HORIZONTAL_DOTS_AMOUNT; i++){
        for (int j = 1; j <= VERTICAL_DOTS_AMOUNT; j++){
            Vector position = Vector(i * HORIZONTAL_GAP_SIZE, j * VERITCAL_GAP_SIZE);
            decorated_enemy_unit->getPosition() = position;
            decorated_enemy_unit->updateGridPosition();
            TestingModule::setNewGridPosition(decorated_enemy_unit);
            std::pair<int, int> new_grid_position = TestingModule::getNewGridPosition(decorated_enemy_unit);
            BOOST_CHECK(abs(i - new_grid_position.first) + abs(j - new_grid_position.second) == 1);
            BOOST_CHECK(new_grid_position.first >= 0);
            BOOST_CHECK(new_grid_position.second >= 0);
            BOOST_CHECK(new_grid_position.first <= HORIZONTAL_DOTS_AMOUNT);
            BOOST_CHECK(new_grid_position.second <= VERTICAL_DOTS_AMOUNT);
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

