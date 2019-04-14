#pragma once

#include <memory>

#include <classes.h>
#include <game.h>

class GameProxy{
private:
    static std::shared_ptr<Game> game;

public:
    GameProxy() = delete;
    static void setGameInstance(std::shared_ptr<Game> game_instance);
    static Vector getHeroUnitPosition();
    static void addEnemyUnitBullet(std::shared_ptr<Bullet> bullet);
    static void addHeroUnitBullet(std::shared_ptr<Bullet> bullet);
    static bool getGridCellValue(std::pair<int, int> cell_index);
    static void setGridCellValue(std::pair<int, int> cell_index, bool new_value);
    static bool checkHeroUnitPosition();
    static bool checkEnemyUnitPosition(sf::FloatRect enemy_unit_bounds);
    static double getTime();
};
