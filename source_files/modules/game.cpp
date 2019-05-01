#include <game.h>
#include <enemy_units_decorators.h>
#include <enemy_units_booster.h>
#include <game_proxy.h>
#include <logging_module.h>

#include <units_settings.h>
#include <technical_settings.h>

Game::Game(UnitsFactory& enemy_units_factory): enemy_units_factory(enemy_units_factory){}

void Game::initialize(UnitsFactory& hero_unit_factory, std::shared_ptr<Controller> controller){
    for (int i = 1; i <= HORIZONTAL_DOTS_AMOUNT; i++){
        for (int j = 1; j <= VERTICAL_DOTS_AMOUNT; j++){
            grid[i][j] = 0;
        }
    }

    timer = 0;
    enemy_units_spawn_timer = 0;
    killed_enemy_units_amount = 0;

    hero_unit = hero_unit_factory.createHeroUnit(Vector(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), controller);
    if (MAKE_LOGS){
        LoggingModule::created(hero_unit);
    }
}

template<class T>
void Game::eraseFromVector(std::vector<T>& vector, int& index){
    std::swap(vector[index], vector.back());
    vector.pop_back();
    index--;
}

void Game::updateHeroUnitBullets(double time){
    for (int i = 0; i < (int)hero_unit_bullets.size(); i++){
        hero_unit_bullets[i]->update(time);

        sf::FloatRect bullet_bounds = hero_unit_bullets[i]->getBounds();
        bool deleted = 0;

        for (int j = 0; j < (int)enemy_units.size(); j++){
            sf::FloatRect enemy_unit_bounds = enemy_units[j]->getBounds();

            if (enemy_unit_bounds.intersects(bullet_bounds)){
                enemy_units[j]->getHealth() -= hero_unit_bullets[i]->damage;

                if (enemy_units[j]->getHealth() <= 0){
                    if (MAKE_LOGS){
                        LoggingModule::killed(enemy_units[j]);
                    }

                    eraseFromVector(enemy_units, j);
                    EnemyUnitsBooster::update();
                    killed_enemy_units_amount++;

                    if (killed_enemy_units_amount % KILLED_ENEMY_UNITS == 0){
                        hero_unit->changeAttackModule();
                    }

                    enemy_units_spawn_timer = std::min(enemy_units_spawn_timer,
                        (int)enemy_units.size() < MIN_ENEMY_UNITS_AMOUNT ?
                        ENEMY_UNITS_SMALL_SPAWN_GAP - TIMER_REDUCTION_AFTER_ENEMY_DEATH : ENEMY_UNITS_BIG_SPAWN_GAP - TIMER_REDUCTION_AFTER_ENEMY_DEATH);
                }

                deleted = 1;
                break;
            }
        }

        if (hero_unit_bullets[i]->range <= 0){
            deleted = 1;
        }

        if (deleted){
            eraseFromVector(hero_unit_bullets, i);
        }
    }
}

void Game::updateEnemyUnitsBullets(double time){
    sf::FloatRect hero_unit_bounds = hero_unit->getBounds();

    for (int i = 0; i < (int)enemy_units_bullets.size(); i++){
        enemy_units_bullets[i]->update(time);
        sf::FloatRect enemy_bullet_bounds = enemy_units_bullets[i]->getBounds();
        bool deleted = 0;

        if (hero_unit_bounds.intersects(enemy_bullet_bounds)){
            hero_unit->getHealth() -= enemy_units_bullets[i]->damage;
            deleted = 1;
        }

        if (enemy_units_bullets[i]->range <= 0){
            deleted = 1;
        }

        if (deleted){
            eraseFromVector(enemy_units_bullets, i);
        }
    }
}

std::pair<int, int> Game::getRandomFreeGridCell(){
    std::vector<std::pair<int, int> > positions;
    sf::FloatRect enemy_unit_bounds;
    enemy_unit_bounds.height = enemy_unit_bounds.width = ENEMY_SHAPE_MAX_SIZE;

    for (int i = 1; i <= HORIZONTAL_DOTS_AMOUNT; i++){
        for (int j = 1; j <= VERTICAL_DOTS_AMOUNT; j++){
            if (grid[i][j] == 0){
                Vector position = Vector(i * HORIZONTAL_GAP_SIZE, j * VERITCAL_GAP_SIZE);
                enemy_unit_bounds.left = position.x - enemy_unit_bounds.width / 2;
                enemy_unit_bounds.top = position.y - enemy_unit_bounds.height / 2;
                if (GameProxy::checkEnemyUnitPosition(enemy_unit_bounds)){
                    positions.push_back((std::make_pair(i, j)));
                }
            }
        }
    }

    if (positions.size() == 0){
        return std::make_pair(-1, -1);
    }
    return positions[rand() % positions.size()];
}

void Game::spawnEnemyUnits(){
    if (((int)enemy_units.size() < MIN_ENEMY_UNITS_AMOUNT && enemy_units_spawn_timer >= ENEMY_UNITS_SMALL_SPAWN_GAP) ||
        ((int)enemy_units.size() < MAX_ENEMY_UNITS_AMOUNT && enemy_units_spawn_timer >= ENEMY_UNITS_BIG_SPAWN_GAP)){

        std::pair<int, int> grid_position = getRandomFreeGridCell();
        if (grid_position != std::make_pair(-1, -1)){
            Vector position = Vector(grid_position.first * HORIZONTAL_GAP_SIZE, grid_position.second * VERITCAL_GAP_SIZE);
            int enemy_type = rand() % 100;
            std::shared_ptr<EnemyUnit> enemy_unit;

            if (enemy_type < WEAK_ENEMY_SPAWN_CHANSE){
                enemy_unit = enemy_units_factory.createWeakEnemyUnit(position);
            } else if (enemy_type < WEAK_ENEMY_SPAWN_CHANSE + STRONG_ENEMY_SPAWN_CHANSE){
                enemy_unit = enemy_units_factory.createStrongEnemyUnit(position);
            } else {
                enemy_unit = enemy_units_factory.createMightyEnemyUnit(position);
            }

            if (MAKE_LOGS){
                LoggingModule::created(enemy_unit);
            }

            if (rand() % 100 < ENEMY_WITH_SUPER_ATTACK_SPAWN_CHANSE){
                enemy_unit = std::make_shared<EnemySuperAttackDecorator>(enemy_unit);
                if (MAKE_LOGS)
                    LoggingModule::created(enemy_unit);
            }

            if (rand() % 100 < ENEMY_WITH_MOVEMENT_SPAWN_CHANSE){
                enemy_unit = std::make_shared<EnemyMovementDecorator>(enemy_unit);
                if (MAKE_LOGS)
                    LoggingModule::created(enemy_unit);
            }

            enemy_unit->updateGridPosition();
            GameProxy::setGridCellValue(enemy_unit->getCurrentGridPosition(), 1);
            EnemyUnitsBooster::addEnemyUnit(enemy_unit);

            enemy_units.push_back(enemy_unit);
        }
        enemy_units_spawn_timer = 0;
    }
}

void Game::update(double time){
    timer += time;
    enemy_units_spawn_timer += time;

    hero_unit->update(time);

    for (auto& enemy_unit : enemy_units){
        enemy_unit->update(time);
    }

    updateHeroUnitBullets(time);
    updateEnemyUnitsBullets(time);

    spawnEnemyUnits();
}
