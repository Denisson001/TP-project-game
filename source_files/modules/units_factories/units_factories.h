#include <SFML/Graphics.hpp>
#include <modules/units/units.cpp>
#include <settings/units_settings.h>
#include <memory>

class UnitsFactory{
/* SINGLTON PATTERN */
protected:
	UnitsFactory(){}
	~UnitsFactory(){}
public:
	UnitsFactory(const UnitsFactory&) = delete;
	UnitsFactory& operator= (const UnitsFactory&) = delete;
/*==================*/
public:
	virtual std::shared_ptr<WeakEnemyUnit> createWeakEnemyUnit(Vector position) = 0;
	virtual std::shared_ptr<StrongEnemyUnit> createStrongEnemyUnit(Vector position) = 0;
	virtual std::shared_ptr<MightyEnemyUnit> createMightyEnemyUnit(Vector position) = 0;
	virtual std::shared_ptr<HeroUnit> createHeroUnit(Vector position) = 0;
};

class CircleUnitsFactory : public UnitsFactory{
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
	std::shared_ptr<HeroUnit> createHeroUnit(Vector position);
};

class SquareUnitsFactory : public UnitsFactory{
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
	std::shared_ptr<HeroUnit> createHeroUnit(Vector position);
};

