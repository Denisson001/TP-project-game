#include <enemy_units_decorators.h>
#include <game_proxy.h>

#include <math_settings.h>

Vector EnemyMovementDecorator::convertGridCellToVector(std::pair<int, int> cell_index){
    return Vector(cell_index.first * HORIZONTAL_GAP_SIZE, cell_index.second * VERITCAL_GAP_SIZE);
}

EnemyMovementDecorator::EnemyMovementDecorator(std::shared_ptr<EnemyUnit> new_decorator_ptr){
    decorator_ptr = new_decorator_ptr;
    new_grid_position = std::make_pair(-1, -1);
}

void EnemyMovementDecorator::setNewGridPosition(){
    std::vector<std::pair<int, int> > directions;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    for (int i = 0; i < 4; i++){
        int new_x = getCurrentGridPosition().first + dx[i];
        int new_y = getCurrentGridPosition().second + dy[i];
        if (new_x >= 1 && new_x < HORIZONTAL_DOTS_AMOUNT && new_y >= 1 && new_y < VERTICAL_DOTS_AMOUNT){
            if (GameProxy::getGridCellValue(std::make_pair(new_x, new_y)))
                continue;
            directions.push_back(std::make_pair(new_x, new_y));
        }
    }
    if (directions.size() == 0)
        return;
    new_grid_position = directions[rand() % directions.size()];
}

void EnemyMovementDecorator::updateMovementModule(double time){
    if (new_grid_position == std::make_pair(-1, -1)){
        setNewGridPosition();
        if (new_grid_position == std::make_pair(-1, -1))
            return;
        GameProxy::setGridCellValue(new_grid_position, 1);
    }

    Vector new_position = convertGridCellToVector(new_grid_position);

    if ((getPosition() - new_position).length() < EPS){
        getPosition() = new_position;
        GameProxy::setGridCellValue(getCurrentGridPosition(), 0);
        getCurrentGridPosition() = new_grid_position;
        new_grid_position = std::make_pair(-1, -1);
    } else {
        Vector vector = (new_position - getPosition()).resize(ENEMY_MOVESPEED);
        Vector prev_position = getPosition();
        if ((getPosition() - new_position).length() < vector.length()){
            getPosition() = new_position;
        } else {
            getPosition() += vector;
        }
        if (!GameProxy::checkEnemyUnitPosition(getBounds()))
            getPosition() = prev_position;
    }
}

void EnemyMovementDecorator::updateAttackModule(double time){
    decorator_ptr->updateAttackModule(time);
}

EnemyMovementDecorator::~EnemyMovementDecorator(){
    if (new_grid_position != std::make_pair(-1, -1)){
        GameProxy::setGridCellValue(new_grid_position, 0);
    }
}
