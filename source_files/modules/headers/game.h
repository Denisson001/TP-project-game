#pragma once

#include <vector>
#include <memory>

#include <classes.h>
#include <units_factories.h>

#include <game_settings.h>

class Game{
#ifdef TESTING_MODE
	friend TestingModule;
#endif

	friend Window;
	friend GameProxy;

private:
	UnitsFactory& enemy_units_factory;
	std::vector<std::shared_ptr<EnemyUnit>> enemy_units;
	std::vector<std::shared_ptr<Bullet>> enemy_bullets;
	std::shared_ptr<HeroUnit> hero_unit;
	void checkHeroUnitBullets();
	void checkEnemyUnitsBullets(double time);
	bool grid[HORIZONTAL_DOTS_AMOUNT][VERTICAL_DOTS_AMOUNT];

public:
	Game(UnitsFactory& enemy_units_factory, UnitsFactory& hero_unit_factory);
	void update(double time);
	void initialize();
};
