#include "../units/units.cpp"
#include "../enemy_units_factories/enemy_units_factories.cpp"
#include "../geometry/geometry.cpp"
#include <vector>

class Game{
public:

	EnemyUnitsFactory* enemyUnitsFactory;
	std::vector<Unit*> enemyUnits;
	//Hero hero;
	void spawnEnemyUnit();

	Game(EnemyUnitsFactory* enemyUnitsFactory);
	void update(double time);
};