#include <units.h>
#include <game_proxy.h>

#include <math_settings.h>

void WeakEnemyUnit::updateMovementModule(double time){}
void StrongEnemyUnit::updateMovementModule(double time){}
void MightyEnemyUnit::updateMovementModule(double time){}

void WeakEnemyUnit::updateAttackModule(double time){
    current_attack_cooldown = std::max((double)0, current_attack_cooldown - time);

    if (current_attack_cooldown < EPS){
        Vector hero_unit_position = GameProxy::getHeroUnitPosition();
        Vector direction = hero_unit_position - position;
        addBullet(direction);
        current_attack_cooldown = max_attack_cooldown;
    }
}

void StrongEnemyUnit::updateAttackModule(double time){
    current_attack_cooldown = std::max((double)0, current_attack_cooldown - time);

    if (current_attack_cooldown < EPS){
        Vector hero_unit_position = GameProxy::getHeroUnitPosition();
        Vector direction = hero_unit_position - position;
        for (int i = -1; i <= 1; i++)
            addBullet(direction.rotate(BULLET_DEFLECTION_ANGLE * i));
        current_attack_cooldown = max_attack_cooldown;
    }
}

void MightyEnemyUnit::updateAttackModule(double time){
    current_attack_cooldown = std::max((double)0, current_attack_cooldown - time);

    if (current_attack_cooldown < EPS){
        Vector hero_unit_position = GameProxy::getHeroUnitPosition();
        Vector direction = hero_unit_position - position;
        for (int i = -2; i <= 2; i++)
            addBullet(direction.rotate(BULLET_DEFLECTION_ANGLE * i));
        current_attack_cooldown = max_attack_cooldown;
    }
}

void WeakEnemyUnit::upgrade(){
    health = std::min(WEAK_ENEMY_MAX_HEALTH, health + WEAK_ENEMY_ADDITIONAL_HEALTH);
}

void StrongEnemyUnit::upgrade(){
    max_attack_cooldown = std::max(STRONG_ENEMY_MIN_ATTACK_COOLDOWN, max_attack_cooldown * STRONG_ENEMY_ATTACK_COOLDOWN_REDUCTION_COEFFICIENT);
}

void MightyEnemyUnit::upgrade(){
    attack_range = std::min(MIGHTY_ENEMY_MAX_ATTACK_RANGE, attack_range * MIGHTY_ENEMY_ADDITIONAL_ATTACK_RANGE_COEFFICIENT);
}

void EnemyUnit::addBullet(Vector direction){
    GameProxy::addEnemyUnitBullet(std::make_shared<Bullet>(getShape()->getFillColor(), getPosition(), direction.resize(BULLET_SPEED), getDamage(), getAttackRange()));
}

void EnemyUnit::updateGridPosition(){
    double best_value = 1e9;
    getCurrentGridPosition() = std::make_pair(1, 1);
    for (int i = 1; i < HORIZONTAL_DOTS_AMOUNT; i++){
        for (int j = 1; j < VERTICAL_DOTS_AMOUNT; j++){
            Vector current_position(i * HORIZONTAL_GAP_SIZE, j * VERITCAL_GAP_SIZE);
            if ((getPosition() - current_position).length() < best_value){
                best_value = (getPosition() - current_position).length();
                getCurrentGridPosition() = std::make_pair(i, j);
            }
        }
    }
}

std::pair<int, int>& EnemyUnit::getCurrentGridPosition(){
    return current_grid_position;
}

EnemyUnit::~EnemyUnit(){
    GameProxy::setGridCellValue(getCurrentGridPosition(), 0);
}
