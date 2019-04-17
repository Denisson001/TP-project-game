#include <game_proxy.h>
#include <geometry.h>

std::shared_ptr<Game> GameProxy::game = nullptr;

void GameProxy::initialize(UnitsFactory& hero_unit_factory, UnitsFactory& enemy_units_factory){
    game = std::make_shared<Game>(enemy_units_factory);
    game->initialize(hero_unit_factory);
}

void GameProxy::update(double time){
    game->update(time);
}

bool GameProxy::end(){
    return game->hero_unit->getHealth() <= 0;
}

std::shared_ptr<Game> GameProxy::getGameInstance(){
    return game;
}

int GameProxy::getKilledEnemyUnitsAmount(){
    return game->killed_enemy_units_amount;
}

Vector GameProxy::getHeroUnitPosition(){
   return game->hero_unit->getPosition();
}

void GameProxy::addEnemyUnitBullet(std::shared_ptr<Bullet> bullet){
   game->enemy_units_bullets.push_back(bullet);
}

void GameProxy::addHeroUnitBullet(std::shared_ptr<Bullet> bullet){
   game->hero_unit_bullets.push_back(bullet);
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

double GameProxy::getTime(){
   return game->timer;
}
