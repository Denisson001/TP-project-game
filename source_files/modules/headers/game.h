#pragma once

#include <vector>
#include <memory>

#include <classes.h>
#include <units_factories.h>

class Game{
	friend Window;
private:
	UnitsFactory& enemy_units_factory;
	std::vector<std::shared_ptr<EnemyUnit>> enemy_units;
	std::shared_ptr<HeroUnit> hero;
	void spawnEnemyUnit();
public:
	Game(UnitsFactory& enemy_units_factory, UnitsFactory& hero_unit_factory);
	void update(double time);
};