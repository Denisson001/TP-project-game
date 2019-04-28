#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include <classes.h>
#include <units.h>
#include <units_settings.h>

class UnitsFactory{
#ifdef TESTING_MODE
	friend TestingModule;
#endif

/* SINGLTON PATTERN */
protected:
	UnitsFactory(){}
	virtual ~UnitsFactory(){}

public:
	UnitsFactory(const UnitsFactory&) = delete;
	UnitsFactory& operator= (const UnitsFactory&) = delete;
/*==================*/

protected:
	void setEnemyUnitSettings(std::shared_ptr<EnemyUnit> enemy_unit, Vector position, double attack_cooldown, double attack_range, int damage, int health);
	void setHeroUnitSettings(std::shared_ptr<HeroUnit> hero_unit, Vector position, double attack_cooldown,
								double attack_range, int damage, int health, std::shared_ptr<Controller> controller);
	virtual std::shared_ptr<sf::Shape> createUnitShape(double unit_shape_size, sf::Color unit_shape_color) = 0;

public:
	virtual std::shared_ptr<WeakEnemyUnit> createWeakEnemyUnit(Vector position) = 0;
	virtual std::shared_ptr<StrongEnemyUnit> createStrongEnemyUnit(Vector position) = 0;
	virtual std::shared_ptr<MightyEnemyUnit> createMightyEnemyUnit(Vector position) = 0;
	virtual std::shared_ptr<HeroUnit> createHeroUnit(Vector position, std::shared_ptr<Controller> controller) = 0;
};

class CircleUnitsFactory : public UnitsFactory{
/* SINGLTON PATTERN */
private:
	CircleUnitsFactory(){}
	~CircleUnitsFactory(){}

public:
	static CircleUnitsFactory& getInstance();
/*==================*/

protected:
	std::shared_ptr<sf::Shape> createUnitShape(double unit_shape_size, sf::Color unit_shape_color);

public:
	std::shared_ptr<WeakEnemyUnit> createWeakEnemyUnit(Vector position);
	std::shared_ptr<StrongEnemyUnit> createStrongEnemyUnit(Vector position);
	std::shared_ptr<MightyEnemyUnit> createMightyEnemyUnit(Vector position);
	std::shared_ptr<HeroUnit> createHeroUnit(Vector position, std::shared_ptr<Controller> controller);
};

class SquareUnitsFactory : public UnitsFactory{
/* SINGLTON PATTERN */
private:
	SquareUnitsFactory(){}
	~SquareUnitsFactory(){}
public:
	static SquareUnitsFactory& getInstance();
/*==================*/

protected:
	std::shared_ptr<sf::Shape> createUnitShape(double unit_shape_size, sf::Color unit_shape_color);

public:
	std::shared_ptr<WeakEnemyUnit> createWeakEnemyUnit(Vector position);
	std::shared_ptr<StrongEnemyUnit> createStrongEnemyUnit(Vector position);
	std::shared_ptr<MightyEnemyUnit> createMightyEnemyUnit(Vector position);
	std::shared_ptr<HeroUnit> createHeroUnit(Vector position, std::shared_ptr<Controller> controller);
};
