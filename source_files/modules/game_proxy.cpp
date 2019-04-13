#include <game_proxy.h>
#include <geometry.h>

std::shared_ptr<Game> GameProxy::game = nullptr;

void GameProxy::setGameInstance(std::shared_ptr<Game> game_instance){
    game = game_instance;
}

Vector GameProxy::getHeroUnitPosition(){
    return game->hero_unit->position;
}

void GameProxy::addEnemyBullet(std::shared_ptr<Bullet> bullet){
    game->enemy_bullets.push_back(bullet);
}

bool GameProxy::getGridCellValue(std::pair<int, int> cell_index){
    return game->grid[cell_index.first][cell_index.second];
}

void GameProxy::setGridCellValue(std::pair<int, int> cell_index, bool new_value){
    game->grid[cell_index.first][cell_index.second] = new_value;
}

bool GameProxy::checkHeroUnitPosition(){
    sf::FloatRect hero_unit_bounds = game->hero_unit->getBounds();
    for (int i = 0; i < (int)game->enemy_units.size(); i++){
        sf::FloatRect enemy_unit_bounds = game->enemy_units[i]->getBounds();
        if (hero_unit_bounds.intersects(enemy_unit_bounds))
            return 0;
    }
    return 1;
}
bool GameProxy::checkEnemyUnitPosition(sf::FloatRect enemy_unit_bounds){
    sf::FloatRect hero_unit_bounds = game->hero_unit->getBounds();
    if (hero_unit_bounds.intersects(enemy_unit_bounds))
        return 0;
    return 1;
}
