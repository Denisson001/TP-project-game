#include <enemy_units_decorators.h>

void EnemyUnitDecorator::getValues(){
    position = decorator_ptr->position;
    shape = decorator_ptr->shape;
    max_attack_cooldown = decorator_ptr->max_attack_cooldown;
    current_attack_cooldown = decorator_ptr->current_attack_cooldown;
    attack_range = decorator_ptr->attack_range;
    damage = decorator_ptr->damage;
    health = decorator_ptr->health;
    current_grid_position = decorator_ptr->current_grid_position;
}

void EnemyUnitDecorator::setValues(){
    decorator_ptr->position = position;
    decorator_ptr->shape = shape;
    decorator_ptr->max_attack_cooldown = max_attack_cooldown;
    decorator_ptr->current_attack_cooldown = current_attack_cooldown;
    decorator_ptr->attack_range = attack_range;
    decorator_ptr->damage = damage;
    decorator_ptr->health = health;
    decorator_ptr->current_grid_position = current_grid_position;
}
