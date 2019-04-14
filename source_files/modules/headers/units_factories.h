#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include <classes.h>
#include <units.h>
#include <units_settings.h>

class UnitsFactory{
/* SINGLTON PATTERN */
protected:
	UnitsFactory(){}
	virtual ~UnitsFactory(){}

public:
	UnitsFactory(const UnitsFactory&) = delete;
	UnitsFactory& operator= (const UnitsFactory&) = delete;
/*==================*/

protected:
	void setUnitSettings(std::shared_ptr<Unit> unit, Vector position, double attack_cooldown, double attack_range, int damage, int health);
	void setEnemyUnitGridPosition(std::shared_ptr<EnemyUnit> enemy_unit);

public:
	virtual std::shared_ptr<WeakEnemyUnit> createWeakEnemyUnit(Vector position) = 0;
	virtual std::shared_ptr<StrongEnemyUnit> createStrongEnemyUnit(Vector position) = 0;
	virtual std::shared_ptr<MightyEnemyUnit> createMightyEnemyUnit(Vector position) = 0;
	virtual std::shared_ptr<HeroUnit> createHeroUnit(Vector position, std::shared_ptr<Controller> controller) = 0;
};

class CircleUnitsFactory : public UnitsFactory{
#ifdef TESTING_MODE
	friend TestingModule;
#endif

/* SINGLTON PATTERN */
private:
	CircleUnitsFactory(){}
	~CircleUnitsFactory(){}

public:
	static CircleUnitsFactory& getInstance();
/*==================*/

private:
	std::shared_ptr<sf::Shape> createUnitShape(double unit_shape_size, sf::Color unit_shape_color);

public:
	std::shared_ptr<WeakEnemyUnit> createWeakEnemyUnit(Vector position);
	std::shared_ptr<StrongEnemyUnit> createStrongEnemyUnit(Vector position);
	std::shared_ptr<MightyEnemyUnit> createMightyEnemyUnit(Vector position);
	std::shared_ptr<HeroUnit> createHeroUnit(Vector position, std::shared_ptr<Controller> controller);
};

class SquareUnitsFactory : public UnitsFactory{
#ifdef TESTING_MODE
	friend TestingModule;
#endif

/* SINGLTON PATTERN */
private:
	SquareUnitsFactory(){}
	~SquareUnitsFactory(){}
public:
	static SquareUnitsFactory& getInstance();
/*==================*/

private:
	std::shared_ptr<sf::Shape> createUnitShape(double unit_shape_size, sf::Color unit_shape_color);

public:
	std::shared_ptr<WeakEnemyUnit> createWeakEnemyUnit(Vector position);
	std::shared_ptr<StrongEnemyUnit> createStrongEnemyUnit(Vector position);
	std::shared_ptr<MightyEnemyUnit> createMightyEnemyUnit(Vector position);
	std::shared_ptr<HeroUnit> createHeroUnit(Vector position, std::shared_ptr<Controller> controller);
};
