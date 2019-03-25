#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include <geometry.h>

class EnemyUnit{
public:
	Vector position;	
	std::shared_ptr<sf::Shape> shape;
	virtual void update(double time) = 0;
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