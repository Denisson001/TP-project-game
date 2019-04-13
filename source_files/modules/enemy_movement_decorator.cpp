#include <enemy_units_decorators.h>
#include <game_proxy.h>

#include <math_settings.h>

Vector EnemyMovementDecorator::convertGridCellToVector(std::pair<int, int> cell_index){
    return Vector(cell_index.first * HORIZONTAL_GAP_SIZE, cell_index.second * VERITCAL_GAP_SIZE);
}

EnemyMovementDecorator::EnemyMovementDecorator(std::shared_ptr<EnemyUnit> new_decorator_ptr){
    decorator_ptr = new_decorator_ptr;
    getValues();
    new_grid_position = std::make_pair(-1, -1);
}

void EnemyMovementDecorator::update(double time){
    updateAttackModule(time);
    updateMovementModule(time);
}

void EnemyMovementDecorator::updateMovementModule(double time){
    if (new_grid_position == std::make_pair(-1, -1)){
        std::vector<std::pair<int, int> > directions;
        for (int dx = -1; dx <= 1; dx++){
            for (int dy = -1; dy <= 1; dy++) if (abs(dx) + abs(dy) == 1){
                int new_x = current_grid_position.first + dx;
                int new_y = current_grid_position.second + dy;
                if (new_x >= 1 && new_x < HORIZONTAL_DOTS_AMOUNT && new_y >= 1 && new_y < VERTICAL_DOTS_AMOUNT){
                    if (GameProxy::getGridCellValue(std::make_pair(new_x, new_y))) continue;
                    directions.push_back(std::make_pair(new_x, new_y));
                }
            }
        }
        if (directions.size() == 0)
            return;
        new_grid_position = directions[rand() % directions.size()];
        GameProxy::setGridCellValue(new_grid_position, 1);
    }

    Vector new_position = convertGridCellToVector(current_grid_position);

    if ((position - new_position).length() < EPS){
        GameProxy::setGridCellValue(current_grid_position, 0);
        current_grid_position = new_grid_position;
        new_grid_position = std::make_pair(-1, -1);
    } else {
        Vector vector = (new_position - position).resize(ENEMY_UNIT_SPEED);
        Vector prev_position = position;
        if ((position - new_position).length() < vector.length()){
            position = new_position;
        } else {
            position += vector;
        }
        if (!GameProxy::checkEnemyUnitPosition(getBounds()))
            position = prev_position;
    }
}

void EnemyMovementDecorator::updateAttackModule(double time){
    setValues();
    decorator_ptr->updateAttackModule(time);
    getValues();
}

EnemyMovementDecorator::~EnemyMovementDecorator(){
    if (new_grid_position != std::make_pair(-1, -1)){
        GameProxy::setGridCellValue(new_grid_position, 0);
    }
}
