#pragma once

#include <vector>
#include <memory>

#include <classes.h>
#include <units_factories.h>

#include <game_settings.h>

class Game{
#ifdef TESTING_MODE
    friend TestingModule;
#endif

    friend Window;
    friend GameProxy;

private:
    UnitsFactory& enemy_units_factory;
    std::vector<std::shared_ptr<EnemyUnit>> enemy_units;
    std::shared_ptr<HeroUnit> hero_unit;
    std::vector<std::shared_ptr<Bullet>> enemy_units_bullets, hero_unit_bullets;
    void updateHeroUnitBullets(double time);
    void updateEnemyUnitsBullets(double time);
    std::pair<int, int> getRandomFreeGridCell();
    void spawnEnemyUnits();
    bool grid[HORIZONTAL_DOTS_AMOUNT + 1][VERTICAL_DOTS_AMOUNT + 1];
    double enemy_units_spawn_timer;
    template<class T>
    void eraseFromVector(std::vector<T>& vector, int& index);

public:
    double timer;
    int killed_enemy_units_amount;
    Game(UnitsFactory& enemy_units_factory);
    void update(double time);
    void initialize(UnitsFactory& hero_unit_factory, std::shared_ptr<Controller> controller);
};
