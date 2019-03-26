#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <algorithm>

#include <geometry.h>
#include <controller.h>
#include <window_settings.h>
#include <units_settings.h>

#include <classes.h>

class Unit{
public:
	Vector position;	
	std::shared_ptr<sf::Shape> shape;
	virtual void update(double time) = 0;
	virtual ~Unit(){}
};

class EnemyUnit : public Unit{
public:
	virtual ~EnemyUnit(){}
};

class WeakEnemyUnit : public EnemyUnit{
public:
	void update(double time);
};

class StrongEnemyUnit : public EnemyUnit{
public:
	void update(double time);
};

class MightyEnemyUnit : public EnemyUnit{
public:
	void update(double time);
};

class HeroUnit : public Unit{
#ifdef TESTING_MODE
	friend TestingModule;
#endif

private:
	void checkBorder();
	void updateMovementModule(double time);
	
public:
	std::shared_ptr<Controller> controller;
	void update(double time);
};
