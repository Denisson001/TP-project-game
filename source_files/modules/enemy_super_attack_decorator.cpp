#include <enemy_units_decorators.h>
#include <game_proxy.h>

#include <math_settings.h>
#include <units_settings.h>

EnemySuperAttackDecorator::EnemySuperAttackDecorator(std::shared_ptr<EnemyUnit> new_decorator_ptr){
    decorator_ptr = new_decorator_ptr;
}

void EnemySuperAttackDecorator::updateMovementModule(double time){
    decorator_ptr->updateMovementModule(time);
}

void EnemySuperAttackDecorator::updateAttackModule(double time){
    getCurrentAttackCooldown() = std::max((double)0, getCurrentAttackCooldown() - time);

    if (getCurrentAttackCooldown() < EPS){
        Vector hero_unit_position = GameProxy::getHeroUnitPosition();
        Vector direction = hero_unit_position - getPosition();
        for (int i = 0; i < SUPER_ATTACK_BULLETS_AMOUNT; i++){
            addBullet(direction.rotate(2 * PI * i / SUPER_ATTACK_BULLETS_AMOUNT));
        }
        getCurrentAttackCooldown() = getMaxAttackCooldown() * SUPER_ATTACK_ADDITIONAL_ATTACK_COOLDOWN_COEFFICIENT;
    }
}
