#pragma once

#include <memory>

#include <classes.h>

class HeroUnitAttackModule{
protected:
    double current_attack_cooldown;
    std::pair<int, int> getDirectionFromController(std::shared_ptr<Controller> controller);
public:
    virtual void update(double time, HeroUnit* hero_unit) = 0;
    void initialize();
    virtual ~HeroUnitAttackModule(){}
};

class SingleShotModule : public HeroUnitAttackModule{
public:
    void update(double time, HeroUnit* hero_unit);
};

class SplitShotModule : public HeroUnitAttackModule{
public:
    void update(double time, HeroUnit* hero_unit);
};

class TripleShotModule : public HeroUnitAttackModule{
private:
    std::pair<int, int> current_attack_direction;
    int created_bullets_amount;
public:
    void update(double time, HeroUnit* hero_unit);
};
