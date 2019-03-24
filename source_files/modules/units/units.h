#include <SFML/Graphics.hpp>
#include <modules/geometry/geometry.cpp>
#include <settings/units_settings.h>
#include <settings/window_settings.h>
#include <memory>
#include <algorithm>

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
private:
	void moveUp(double value);
	void moveDown(double value);
	void moveLeft(double value);
	void moveRight(double value);
	void checkBorder();
public:
	void update(double time);
};
