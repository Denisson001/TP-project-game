#pragma once

#include <memory>

#include <units.h>

#include <game_settings.h>

class EnemyUnitDecorator : public EnemyUnit{
protected:
    std::shared_ptr<EnemyUnit> decorator_ptr;
public:
    Vector& getPosition();
	std::shared_ptr<sf::Shape>& getShape();
	double& getMaxAttackCooldown();
	double& getCurrentAttackCooldown();
	double& getAttackRange();
	int& getDamage();
	int& getHealth();
    std::pair<int, int>& getCurrentGridPosition();
    void upgrade();
};

class EnemySuperAttackDecorator : public EnemyUnitDecorator{
protected:
	void updateAttackModule(double time);
	void updateMovementModule(double time);

public:
    EnemySuperAttackDecorator(std::shared_ptr<EnemyUnit> new_decorator_ptr);
};

class EnemyMovementDecorator : public EnemyUnitDecorator{
#ifdef TESTING_MODE
	friend TestingModule;
#endif

private:
    std::pair<int, int> new_grid_position;
    Vector convertGridCellToVector(std::pair<int, int> cell_index);
    void setNewGridPosition();

protected:
    void updateAttackModule(double time);
    void updateMovementModule(double time);

public:
    EnemyMovementDecorator(std::shared_ptr<EnemyUnit> new_decorator_ptr);
    ~EnemyMovementDecorator();
};
