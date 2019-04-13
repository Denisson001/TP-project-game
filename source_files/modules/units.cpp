#include <units.h>

#include <game_proxy.h>

#include <game_settings.h>

void Unit::update(double time){
    updateAttackModule(time);
    updateMovementModule(time);
}

sf::FloatRect Unit::getBounds(){
    shape->setPosition(position.x, position.y);
    sf::FloatRect bounds = shape->getGlobalBounds();
	bounds.left += bounds.width * (1 - UNIT_SHAPE_BOUNDS_COEFFICIENT) / (double)2;
	bounds.top += bounds.height * (1 - UNIT_SHAPE_BOUNDS_COEFFICIENT) / (double)2;
	bounds.height *= UNIT_SHAPE_BOUNDS_COEFFICIENT;
	bounds.width *= UNIT_SHAPE_BOUNDS_COEFFICIENT;
    return bounds;
}

void EnemyUnit::updateGridPosition(){
    double best_value = 1e9;
    current_grid_position = std::make_pair(1, 1);
    for (int i = 1; i < HORIZONTAL_DOTS_AMOUNT; i++){
        for (int j = 1; j < VERTICAL_DOTS_AMOUNT; j++){
            Vector current_position(i * HORIZONTAL_GAP_SIZE, j * VERITCAL_GAP_SIZE);
            if ((position - current_position).length() < best_value){
                best_value = (position - current_position).length();
                current_grid_position = std::make_pair(i, j);
            }
        }
    }
}

EnemyUnit::~EnemyUnit(){
    GameProxy::setGridCellValue(current_grid_position, 0);
}
