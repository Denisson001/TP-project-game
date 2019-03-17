#include <SFML/Graphics.hpp>
#include "../units/units.cpp"
#include "../../settings/units_settings.h"

class EnemyUnitsFactory{
public:
	virtual WeakEnemyUnit* createWeakEnemyUnit(Vector position) = 0;
	virtual StrongEnemyUnit* createStrongEnemyUnit(Vector position) = 0;
	virtual MightyEnemyUnit* createMightyEnemyUnit(Vector position) = 0;
	virtual ~EnemyUnitsFactory(){}
};

class CircleEnemyUnitsFactory : public EnemyUnitsFactory{
public:
	WeakEnemyUnit* createWeakEnemyUnit(Vector position);
	StrongEnemyUnit* createStrongEnemyUnit(Vector position);
	MightyEnemyUnit* createMightyEnemyUnit(Vector position);
};

class SquareEnemyUnitsFactory : public EnemyUnitsFactory{
public:
	WeakEnemyUnit* createWeakEnemyUnit(Vector position);
	StrongEnemyUnit* createStrongEnemyUnit(Vector position);
	MightyEnemyUnit* createMightyEnemyUnit(Vector position);
};

