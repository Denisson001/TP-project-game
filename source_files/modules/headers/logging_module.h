#pragma once

#include <memory>
#include <vector>

#include <geometry.h>
#include <enemy_units_decorators.h>
#include <classes.h>

class LoggingModule{
#ifdef TESTING_MODE
    friend TestingModule;
#endif

private:
    static std::vector<std::string> text;
    static void printMessages();
    static void addMessage(const std::string& str);
    static void addEnemyUnitSettings(std::shared_ptr<EnemyUnit> enemy_unit);
    static void addHeroUnitSettings(std::shared_ptr<HeroUnit> hero_unit);

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
