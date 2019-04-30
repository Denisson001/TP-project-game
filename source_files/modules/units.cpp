#include <units.h>

#include <game_settings.h>

void Unit::update(double time){
    updateAttackModule(time);
    updateMovementModule(time);
}

sf::FloatRect Unit::getBounds(){
    getShape()->setPosition(getPosition().x, getPosition().y);
    sf::FloatRect bounds = getShape()->getGlobalBounds();
    bounds.left += bounds.width * (1 - UNIT_SHAPE_BOUNDS_COEFFICIENT) / (double)2;
    bounds.top += bounds.height * (1 - UNIT_SHAPE_BOUNDS_COEFFICIENT) / (double)2;
    bounds.height *= UNIT_SHAPE_BOUNDS_COEFFICIENT;
    bounds.width *= UNIT_SHAPE_BOUNDS_COEFFICIENT;
    return bounds;
}

Vector& Unit::getPosition(){
    return position;
}

std::shared_ptr<sf::Shape>& Unit::getShape(){
    return shape;
}

double& Unit::getAttackRange(){
    return attack_range;
}

int& Unit::getDamage(){
    return damage;
}

int& Unit::getHealth(){
    return health;
}

double& Unit::getMaxAttackCooldown(){
    return max_attack_cooldown;
}
