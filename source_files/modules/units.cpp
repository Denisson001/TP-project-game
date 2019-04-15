#include <units.h>

#include <game_proxy.h>

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

EnemyUnit::~EnemyUnit(){
    GameProxy::setGridCellValue(getCurrentGridPosition(), 0);
}

Vector& Unit::getPosition(){
    return position;
}

std::shared_ptr<sf::Shape>& Unit::getShape(){
    return shape;
}

double& Unit::getMaxAttackCooldown(){
    return max_attack_cooldown;
}

double& Unit::getCurrentAttackCooldown(){
    return current_attack_cooldown;
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

std::pair<int, int>& EnemyUnit::getCurrentGridPosition(){
    return current_grid_position;
}
