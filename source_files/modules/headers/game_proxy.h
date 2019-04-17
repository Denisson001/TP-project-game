#pragma once

#include <memory>

#include <classes.h>
#include <game.h>

class GameProxy{
private:
    static std::shared_ptr<Game> game;

public:
    GameProxy() = delete;
    static Vector getHeroUnitPosition();
    static void addEnemyUnitBullet(std::shared_ptr<Bullet> bullet);
    static void addHeroUnitBullet(std::shared_ptr<Bullet> bullet);
    static bool getGridCellValue(std::pair<int, int> cell_index);
    static void setGridCellValue(std::pair<int, int> cell_index, bool new_value);
    static bool checkHeroUnitPosition();
    static bool checkEnemyUnitPosition(sf::FloatRect enemy_unit_bounds);
    static double getTime();
    static void initialize(UnitsFactory& hero_unit_factory, UnitsFactory& enemy_units_factory);
    static void update(double time);
    static bool end();
    static std::shared_ptr<Game> getGameInstance();
    static int getKilledEnemyUnitsAmount();
};
