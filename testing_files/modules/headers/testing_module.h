#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include <game.h>
#include <enemy_units_booster.h>

class TestingModule{
public:
	static std::shared_ptr<HeroUnit> getHeroUnitFromGame(std::shared_ptr<Game> game);
	static std::vector<std::shared_ptr<Bullet>>& getEnemyUnitsBulletsFromGame(std::shared_ptr<Game> game);
	static std::vector<std::shared_ptr<Bullet>>& getHeroUnitBulletsFromGame(std::shared_ptr<Game> game);
	static std::vector<std::shared_ptr<EnemyUnit>>& getEnemyUnitsFromGame(std::shared_ptr<Game> game);
	static int getEnemyUnitsAmountFromEnemyUnitsBooster();
	static std::shared_ptr<sf::Shape> callCreateUnitShapeFromCircleUnitsFactory(double unit_shape_size, sf::Color unit_shape_color);
	static std::shared_ptr<sf::Shape> callCreateUnitShapeFromSquareUnitsFactory(double unit_shape_size, sf::Color unit_shape_color);
};
