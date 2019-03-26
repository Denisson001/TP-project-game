#pragma once

#include <vector>
#include <memory>

#include <classes.h>
#include <units_factories.h>

class Game{
#ifdef TESTING_MODE
	friend TestingModule;
#endif

	friend Window;
	
private:
	UnitsFactory& enemy_units_factory;
	std::vector<std::shared_ptr<EnemyUnit>> enemy_units;
	std::shared_ptr<HeroUnit> hero_unit;

public:
	Game(UnitsFactory& enemy_units_factory, UnitsFactory& hero_unit_factory);
	void update(double time);
};