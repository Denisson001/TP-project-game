#pragma once

#include <memory>

#include <units.h>

#include <game_settings.h>

class EnemyUnitDecorator : public EnemyUnit{
protected:
    std::shared_ptr<EnemyUnit> decorator_ptr;
    void setValues();
    void getValues();
};

class EnemySuperAttackDecorator : public EnemyUnitDecorator{
protected:
	void updateAttackModule(double time);
	void updateMovementModule(double time);

public:
    EnemySuperAttackDecorator(std::shared_ptr<EnemyUnit> new_decorator_ptr);
	void update(double time);
};

class EnemyMovementDecorator : public EnemyUnitDecorator{
private:
    std::pair<int, int> new_grid_position;
    Vector convertGridCellToVector(std::pair<int, int> cell_index);
    
protected:
    void updateAttackModule(double time);
    void updateMovementModule(double time);

public:
    EnemyMovementDecorator(std::shared_ptr<EnemyUnit> new_decorator_ptr);
    void update(double time);
    ~EnemyMovementDecorator();
};
