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
        Vector vector = hero_unit_position - position;
		GameProxy::addEnemyUnitBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED), damage, attack_range));
		current_attack_cooldown = max_attack_cooldown;
	}
}

void StrongEnemyUnit::updateAttackModule(double time){
    current_attack_cooldown = std::max((double)0, current_attack_cooldown - time);

    if (current_attack_cooldown < EPS){
        Vector hero_unit_position = GameProxy::getHeroUnitPosition();
        Vector vector = hero_unit_position - position;
        GameProxy::addEnemyUnitBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED), damage, attack_range));
        GameProxy::addEnemyUnitBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED).rotate(BULLET_DEFLECTION_ANGLE), damage, attack_range));
        GameProxy::addEnemyUnitBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED).rotate(-BULLET_DEFLECTION_ANGLE), damage, attack_range));
        current_attack_cooldown = max_attack_cooldown;
    }
}

void MightyEnemyUnit::updateAttackModule(double time){
    current_attack_cooldown = std::max((double)0, current_attack_cooldown - time);

    if (current_attack_cooldown < EPS){
        Vector hero_unit_position = GameProxy::getHeroUnitPosition();
        Vector vector = hero_unit_position - position;
        GameProxy::addEnemyUnitBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED), damage, attack_range));
        GameProxy::addEnemyUnitBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED).rotate(BULLET_DEFLECTION_ANGLE), damage, attack_range));
        GameProxy::addEnemyUnitBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED).rotate(2 * BULLET_DEFLECTION_ANGLE), damage, attack_range));
        GameProxy::addEnemyUnitBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED).rotate(-BULLET_DEFLECTION_ANGLE), damage, attack_range));
        GameProxy::addEnemyUnitBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED).rotate(-2 * BULLET_DEFLECTION_ANGLE), damage, attack_range));
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
