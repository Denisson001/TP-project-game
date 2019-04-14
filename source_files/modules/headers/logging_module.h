#pragma once

#include <memory>
#include <vector>

#include <geometry.h>
#include <enemy_units_decorators.h>
#include <classes.h>


class LoggingModule{
private:
    static std::vector<std::string> text;
    static std::string convertTimeToString(double time);
    static std::string convertIntToString(int value);
    static std::string convertVectorToString(Vector vector);
    static std::string getTime();
    static void printMessages();
    static void addMessage(const std::string& str);
    static void addUnitSettings(std::shared_ptr<Unit> unit);

public:
    LoggingModule() = delete;
    static void initialize(int seed);
    static void created(std::shared_ptr<Unit> unit);
    static void created(std::shared_ptr<HeroUnit> hero_unit);
    static void created(std::shared_ptr<WeakEnemyUnit> enemy_unit);
    static void created(std::shared_ptr<StrongEnemyUnit> enemy_unit);
    static void created(std::shared_ptr<MightyEnemyUnit> enemy_unit);
    static void created(std::shared_ptr<EnemySuperAttackDecorator> decorator);
    static void created(std::shared_ptr<EnemyMovementDecorator> decorator);
    static void killed(std::shared_ptr<Unit> unit);
    static void killed(std::shared_ptr<HeroUnit> hero_unit);
    static void killed(std::shared_ptr<WeakEnemyUnit> enemy_unit);
    static void killed(std::shared_ptr<StrongEnemyUnit> enemy_unit);
    static void killed(std::shared_ptr<MightyEnemyUnit> enemy_unit);
    static void killed(std::shared_ptr<EnemySuperAttackDecorator> decorator);
    static void killed(std::shared_ptr<EnemyMovementDecorator> decorator);
};
