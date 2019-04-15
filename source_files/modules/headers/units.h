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
	Vector position;
	std::shared_ptr<sf::Shape> shape;
	double max_attack_cooldown, current_attack_cooldown, attack_range;
	int damage, health;

public:
	virtual void update(double time);
	sf::FloatRect getBounds();
	virtual ~Unit(){}
	virtual Vector& getPosition();
	virtual std::shared_ptr<sf::Shape>& getShape();
	virtual double& getMaxAttackCooldown();
	virtual double& getCurrentAttackCooldown();
	virtual double& getAttackRange();
	virtual int& getDamage();
	virtual int& getHealth();
};

class EnemyUnit : public Unit{
protected:
	std::pair<int, int> current_grid_position;

public:
	void updateGridPosition();
	virtual ~EnemyUnit();
	virtual std::pair<int, int>& getCurrentGridPosition();
	virtual void upgrade() = 0;
};

class WeakEnemyUnit : public EnemyUnit{
protected:
	void updateAttackModule(double time);
	void updateMovementModule(double time);

public:
	void upgrade();
};

class StrongEnemyUnit : public EnemyUnit{
protected:
	void updateAttackModule(double time);
	void updateMovementModule(double time);

public:
	void upgrade();
};

class MightyEnemyUnit : public EnemyUnit{
protected:
	void updateAttackModule(double time);
	void updateMovementModule(double time);

public:
	void upgrade();
};

class HeroUnit : public Unit{
#ifdef TESTING_MODE
	friend TestingModule;
#endif

private:
	void checkBorder();
	std::shared_ptr<Controller> controller;

protected:
	void updateAttackModule(double time);
	void updateMovementModule(double time);

public:
	std::shared_ptr<Controller>& getController();
};
