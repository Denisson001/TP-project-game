#include <hero_unit_attack_module.h>

#include <SFML/Graphics.hpp>

#include <geometry.h>
#include <game_proxy.h>

#include <units_settings.h>
#include <math_settings.h>

std::pair<int, int> HeroUnitAttackModule::getDirectionFromController(std::shared_ptr<Controller> controller){
    int dx = 0, dy = 0;
    if (controller->isUpArrowKeyPressed()) dy -= 1;
    if (controller->isDownArrowKeyPressed()) dy += 1;
    if (controller->isLeftArrowKeyPressed()) dx -= 1;
    if (controller->isRightArrowKeyPressed()) dx += 1;
    return std::make_pair(dx, dy);
}

void HeroUnitAttackModule::initialize(){
    current_attack_cooldown = 0;
}

void SingleShotModule::update(double time, HeroUnit* hero_unit){
    current_attack_cooldown = std::max((double)0, current_attack_cooldown - time);

    if (current_attack_cooldown < EPS){
        std::pair<int, int> direction = getDirectionFromController(hero_unit->getController());
        int dx = direction.first, dy = direction.second;
        if (dx != 0 || dy != 0){
            hero_unit->addBullet(Vector(dx, dy));
            current_attack_cooldown = hero_unit->getMaxAttackCooldown();
        }
    }
}

void SplitShotModule::update(double time, HeroUnit* hero_unit){
    current_attack_cooldown = std::max((double)0, current_attack_cooldown - time);

    if (current_attack_cooldown < EPS){
        std::pair<int, int> direction = getDirectionFromController(hero_unit->getController());
        int dx = direction.first, dy = direction.second;
        if (dx != 0 || dy != 0){
            for (int i = -1; i <= 1; i++){
                hero_unit->addBullet(Vector(dx, dy).rotate(BULLET_DEFLECTION_ANGLE * i));
            }
            current_attack_cooldown = hero_unit->getMaxAttackCooldown();
        }
    }
}

void TripleShotModule::update(double time, HeroUnit* hero_unit){
    current_attack_cooldown = std::max((double)0, current_attack_cooldown - time);

    if (current_attack_cooldown < EPS){
        if (created_bullets_amount == 0){
            std::pair<int, int> direction = getDirectionFromController(hero_unit->getController());
            int dx = direction.first, dy = direction.second;
            if (dx != 0 || dy != 0){
                hero_unit->addBullet(Vector(dx, dy));
                current_attack_direction = direction;
                current_attack_cooldown = HERO_MINI_ATTACK_COOLDOWN;
                created_bullets_amount = 1;
            }
        } else {
            int dx = current_attack_direction.first, dy = current_attack_direction.second;
            hero_unit->addBullet(Vector(dx, dy));
            created_bullets_amount++;
            if (created_bullets_amount == 3){
                created_bullets_amount = 0;
                current_attack_cooldown = hero_unit->getMaxAttackCooldown();
            } else {
                current_attack_cooldown = HERO_MINI_ATTACK_COOLDOWN;
            }
        }
    }
}
