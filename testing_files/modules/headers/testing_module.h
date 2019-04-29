#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include <game.h>
#include <enemy_units_booster.h>
#include <hero_unit_attack_module.h>

class TestingModule{
public:
	static std::shared_ptr<HeroUnit> getHeroUnit(std::shared_ptr<Game> game);
	static std::vector<std::shared_ptr<Bullet>>& getEnemyUnitsBullets(std::shared_ptr<Game> game);
	static std::vector<std::shared_ptr<Bullet>>& getHeroUnitBullets(std::shared_ptr<Game> game);
	static std::vector<std::shared_ptr<EnemyUnit>>& getEnemyUnits(std::shared_ptr<Game> game);
	static int getEnemyUnitsAmount();
	static std::shared_ptr<sf::Shape> createCircleUnitShape(UnitsFactory& units_factory, double unit_shape_size, sf::Color unit_shape_color);
	static std::pair<int, int> getDirectionFromController(std::shared_ptr<HeroUnitAttackModule> attack_module, std::shared_ptr<Controller> controller);
	static void updateAttackModule(std::shared_ptr<EnemyUnit> enemy_unit, double time);
};
