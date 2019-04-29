#include <enemy_units_booster.h>

std::list<std::shared_ptr<EnemyUnit>> EnemyUnitsBooster::enemy_units;

void EnemyUnitsBooster::addEnemyUnit(std::shared_ptr<EnemyUnit> enemy_unit){
    enemy_units.push_back(enemy_unit);
}

void EnemyUnitsBooster::update(){
    for (auto it = enemy_units.begin(); it != enemy_units.end(); it++){
        auto enemy_unit = *it;
        if (enemy_unit->getHealth() <= 0){
            enemy_units.erase(it);
            break;
        } else {
            enemy_unit->upgrade();
        }
    }
}
