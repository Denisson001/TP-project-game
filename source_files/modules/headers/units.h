#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <algorithm>

#include <bullet.h>
#include <geometry.h>
#include <controller.h>
#include <window_settings.h>
#include <units_settings.h>

#include <classes.h>

class Unit{
	friend EnemySuperAttackDecorator;
	friend EnemyMovementDecorator;

protected:
	virtual void updateAttackModule(double time) = 0;
	virtual void updateMovementModule(double time) = 0;

public:
	Vector position;
	std::shared_ptr<sf::Shape> shape;
	double max_attack_cooldown, current_attack_cooldown, attack_range;
	int damage, health;
	virtual void update(double time);
	sf::FloatRect getBounds();
	virtual ~Unit(){}
};

class EnemyUnit : public Unit{
public:
	std::pair<int, int> current_grid_position;
	void updateGridPosition();
	virtual ~EnemyUnit();
};

class WeakEnemyUnit : public EnemyUnit{
protected:
	void updateAttackModule(double time);
	void updateMovementModule(double time);
};

class StrongEnemyUnit : public EnemyUnit{
protected:
	void updateAttackModule(double time);
	void updateMovementModule(double time);
};

class MightyEnemyUnit : public EnemyUnit{
protected:
	void updateAttackModule(double time);
	void updateMovementModule(double time);
};

class HeroUnit : public Unit{
#ifdef TESTING_MODE
	friend TestingModule;
#endif

private:
	void checkBorder();

protected:
	void updateAttackModule(double time);
	void updateMovementModule(double time);

public:
	std::shared_ptr<Controller> controller;
	std::vector<std::shared_ptr<Bullet> > bullets;
};
