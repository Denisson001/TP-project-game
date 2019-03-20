#include <SFML/Graphics.hpp>
#include "../geometry/geometry.cpp"
#include "../../settings/units_settings.h"
#include <memory>

class Unit{
public:
	Vector position;	
	std::shared_ptr<sf::Shape> shape;
	virtual void update(double time) = 0;
	virtual ~Unit(){}
};

class WeakEnemyUnit : public Unit{
public:
	void update(double time);
};

class StrongEnemyUnit : public Unit{
public:
	void update(double time);
};

class MightyEnemyUnit : public Unit{
public:
	void update(double time);
};

class HeroUnit : public Unit{
public:
	void update(double time);
};
