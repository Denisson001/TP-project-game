#include <enemy_units_decorators.h>
#include <game_proxy.h>

#include <math_settings.h>

EnemySuperAttackDecorator::EnemySuperAttackDecorator(std::shared_ptr<EnemyUnit> new_decorator_ptr){
    decorator_ptr = new_decorator_ptr;
    getValues();
}

void EnemySuperAttackDecorator::update(double time){
    updateAttackModule(time);
    updateMovementModule(time);
}

void EnemySuperAttackDecorator::updateMovementModule(double time){
    setValues();
    decorator_ptr->updateMovementModule(time);
    getValues();
}

void EnemySuperAttackDecorator::updateAttackModule(double time){
    current_attack_cooldown = std::max((double)0, current_attack_cooldown - time);

    if (current_attack_cooldown < EPS){
        Vector hero_unit_position = GameProxy::getHeroUnitPosition();
        Vector vector = hero_unit_position - position;
        for (int i = 0; i < 10; i++){
            std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED).rotate(2 * PI * i / 10), damage, attack_range);
            GameProxy::addEnemyBullet(bullet);
        }
        current_attack_cooldown = 2 * max_attack_cooldown;
    }
}
