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
		GameProxy::addEnemyBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED), damage, attack_range));
		current_attack_cooldown = max_attack_cooldown;
	}
}

void StrongEnemyUnit::updateAttackModule(double time){
    current_attack_cooldown = std::max((double)0, current_attack_cooldown - time);

    if (current_attack_cooldown < EPS){
        Vector hero_unit_position = GameProxy::getHeroUnitPosition();
        Vector vector = hero_unit_position - position;
        GameProxy::addEnemyBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED), damage, attack_range));
        GameProxy::addEnemyBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED).rotate(BULLET_DEFLECTION_ANGLE), damage, attack_range));
        GameProxy::addEnemyBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED).rotate(-BULLET_DEFLECTION_ANGLE), damage, attack_range));
        current_attack_cooldown = max_attack_cooldown;
    }
}

void MightyEnemyUnit::updateAttackModule(double time){
    current_attack_cooldown = std::max((double)0, current_attack_cooldown - time);

    if (current_attack_cooldown < EPS){
        Vector hero_unit_position = GameProxy::getHeroUnitPosition();
        Vector vector = hero_unit_position - position;
        GameProxy::addEnemyBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED), damage, attack_range));
        GameProxy::addEnemyBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED).rotate(BULLET_DEFLECTION_ANGLE), damage, attack_range));
        GameProxy::addEnemyBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED).rotate(2 * BULLET_DEFLECTION_ANGLE), damage, attack_range));
        GameProxy::addEnemyBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED).rotate(-BULLET_DEFLECTION_ANGLE), damage, attack_range));
        GameProxy::addEnemyBullet(std::make_shared<Bullet>(shape->getFillColor(), position, vector.resize(BULLET_SPEED).rotate(-2 * BULLET_DEFLECTION_ANGLE), damage, attack_range));
        current_attack_cooldown = max_attack_cooldown;
    }
}
