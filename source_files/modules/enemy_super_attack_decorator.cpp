#include <enemy_units_decorators.h>
#include <game_proxy.h>

#include <math_settings.h>

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
        Vector vector = hero_unit_position - getPosition();
        for (int i = 0; i < 10; i++){
            std::shared_ptr<Bullet> bullet =
                std::make_shared<Bullet>(getShape()->getFillColor(), getPosition(), vector.resize(BULLET_SPEED).rotate(2 * PI * i / 10), getDamage(), getAttackRange());
            GameProxy::addEnemyUnitBullet(bullet);
        }
        getCurrentAttackCooldown() = 2 * getMaxAttackCooldown();
    }
}
