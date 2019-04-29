#include <enemy_units_decorators.h>

Vector& EnemyUnitDecorator::getPosition(){
    return decorator_ptr->getPosition();
}

std::shared_ptr<sf::Shape>& EnemyUnitDecorator::getShape(){
    return decorator_ptr->getShape();
}

double& EnemyUnitDecorator::getMaxAttackCooldown(){
    return decorator_ptr->getMaxAttackCooldown();
}

double& EnemyUnitDecorator::getCurrentAttackCooldown(){
    return decorator_ptr->getCurrentAttackCooldown();
}

double& EnemyUnitDecorator::getAttackRange(){
    return decorator_ptr->getAttackRange();
}

int& EnemyUnitDecorator::getDamage(){
    return decorator_ptr->getDamage();
}

int& EnemyUnitDecorator::getHealth(){
    return decorator_ptr->getHealth();
}

std::pair<int, int>& EnemyUnitDecorator::getCurrentGridPosition(){
    return decorator_ptr->getCurrentGridPosition();
}

void EnemyUnitDecorator::upgrade(){
    decorator_ptr->upgrade();
}
