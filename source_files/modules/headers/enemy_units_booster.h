#pragma once

#include <units.h>

#include <list>
#include <memory>

class EnemyUnitsBooster{
private:
    static std::list<std::shared_ptr<EnemyUnit>> enemy_units;
public:
    static void addEnemyUnit(std::shared_ptr<EnemyUnit> enemy_unit);
    static void update();
};
