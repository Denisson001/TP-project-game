#include <modules/units/units.cpp>
#include <modules/units_factories/units_factories.cpp>
#include <modules/geometry/geometry.cpp>
#include <vector>
#include <memory>

class Window;

class Game{
	friend Window;
private:
	UnitsFactory& enemy_units_factory;
	std::vector<std::shared_ptr<Unit>> enemy_units;
	std::shared_ptr<HeroUnit> hero;
	void spawnEnemyUnit();
public:
	Game(UnitsFactory& enemy_units_factory, UnitsFactory& hero_unit_factory);
	void update(double time);
};