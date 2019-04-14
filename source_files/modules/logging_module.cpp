#include <logging_module.h>

#include <game_proxy.h>

#include <fstream>

#include <technical_settings.h>

std::vector<std::string> LoggingModule::text;

std::string LoggingModule::convertTimeToString(double time){
    int value = time;
    std::string str;
    while(value > 0){
        str += '0' + value % 10;
        value /= 10;
    }
    while(str.size() < 2)
        str += '0';
    reverse(str.begin(), str.end());
    return str;
}

std::string LoggingModule::convertIntToString(int value){
    if (value == 0)
        return "0";
    bool minus = 0;
    if (value < 0){
        value = -value;
        minus = 1;
    }
    std::string str;
    while(value){
        str += '0' + value % 10;
        value /= 10;
    }
    if (minus)
        str += "-";
    reverse(str.begin(), str.end());
    return str;
}

std::string LoggingModule::convertVectorToString(Vector vector){
    return "(" + convertIntToString((int)vector.x) + ", " + convertIntToString((int)vector.y) + ")";
}

std::string LoggingModule::getTime(){
    std::string str;
    str += '[';
    double time = GameProxy::getTime() / 1000;
    int value = time;
    str += convertTimeToString(value / 60);
    str += ':';
    str += convertTimeToString(value % 60);
    str += ']';
    return str;
}

void LoggingModule::printMessages(){
    if (text.size() == 0)
        return;
    std::ofstream file;
    file.open(LOG_FILE_PATH, std::fstream::app);
    std::string time = getTime() + " ";
    file << time << text[0] << "\n";
    for (int i = 1; i < (int)text.size(); i++){
        for (int j = 0; j < (int)time.size(); j++)
            file << " ";
        file << text[i] << "\n";
    }
    file << "\n\n";
    file.close();
    text.clear();
}

void LoggingModule::addMessage(const std::string& str){
    text.push_back(str);
}

void LoggingModule::initialize(int seed){
    std::ofstream file;
    file.open(LOG_FILE_PATH, std::fstream::out);
    file << "*** START LOGGING ***\n";
    file << "seed: " << seed << "\n\n";
    file.close();
}

void LoggingModule::addUnitSettings(std::shared_ptr<Unit> unit){
    addMessage("Damage: " + convertIntToString(unit->damage));
    addMessage("Health: " + convertIntToString(unit->health));
    addMessage("Attack range: " + convertIntToString(unit->attack_range));
    addMessage("Attack cooldown: " + convertIntToString(unit->max_attack_cooldown));
}

void LoggingModule::created(std::shared_ptr<Unit> unit){
    if (std::dynamic_pointer_cast<WeakEnemyUnit>(unit) != nullptr)
        created(std::dynamic_pointer_cast<WeakEnemyUnit>(unit));

    else if (std::dynamic_pointer_cast<StrongEnemyUnit>(unit) != nullptr)
        created(std::dynamic_pointer_cast<StrongEnemyUnit>(unit));

    else if (std::dynamic_pointer_cast<MightyEnemyUnit>(unit) != nullptr)
        created(std::dynamic_pointer_cast<MightyEnemyUnit>(unit));

    else if (std::dynamic_pointer_cast<EnemySuperAttackDecorator>(unit) != nullptr)
        created(std::dynamic_pointer_cast<EnemySuperAttackDecorator>(unit));

    else if (std::dynamic_pointer_cast<EnemyMovementDecorator>(unit) != nullptr)
        created(std::dynamic_pointer_cast<EnemyMovementDecorator>(unit));

    else if (std::dynamic_pointer_cast<HeroUnit>(unit) != nullptr)
        created(std::dynamic_pointer_cast<HeroUnit>(unit));
}

void LoggingModule::created(std::shared_ptr<HeroUnit> hero_unit){
    addMessage("HeroUnit created at position: " + convertVectorToString(hero_unit->position));
    addUnitSettings(hero_unit);
    printMessages();
}

void LoggingModule::created(std::shared_ptr<WeakEnemyUnit> enemy_unit){
    addMessage("WeakEnemyUnit created at position: " + convertVectorToString(enemy_unit->position));
    addUnitSettings(enemy_unit);
    printMessages();
}

void LoggingModule::created(std::shared_ptr<StrongEnemyUnit> enemy_unit){
    addMessage("StrongEnemyUnit created at position: " + convertVectorToString(enemy_unit->position));
    addUnitSettings(enemy_unit);
    printMessages();
}

void LoggingModule::created(std::shared_ptr<MightyEnemyUnit> enemy_unit){
    addMessage("MightyEnemyUnit created at position: " + convertVectorToString(enemy_unit->position));
    addUnitSettings(enemy_unit);
    printMessages();
}

void LoggingModule::created(std::shared_ptr<EnemySuperAttackDecorator> decorator){
    addMessage("EnemySuperAttackDecorator has been applied");
    printMessages();
}

void LoggingModule::created(std::shared_ptr<EnemyMovementDecorator> decorator){
    addMessage("EnemyMovementDecorator has been applied");
    printMessages();
}

void LoggingModule::killed(std::shared_ptr<Unit> unit){
    if (std::dynamic_pointer_cast<WeakEnemyUnit>(unit) != nullptr)
        killed(std::dynamic_pointer_cast<WeakEnemyUnit>(unit));

    else if (std::dynamic_pointer_cast<StrongEnemyUnit>(unit) != nullptr)
        killed(std::dynamic_pointer_cast<StrongEnemyUnit>(unit));

    else if (std::dynamic_pointer_cast<MightyEnemyUnit>(unit) != nullptr)
        killed(std::dynamic_pointer_cast<MightyEnemyUnit>(unit));

    else if (std::dynamic_pointer_cast<EnemySuperAttackDecorator>(unit) != nullptr)
        killed(std::dynamic_pointer_cast<EnemySuperAttackDecorator>(unit));

    else if (std::dynamic_pointer_cast<EnemyMovementDecorator>(unit) != nullptr)
        killed(std::dynamic_pointer_cast<EnemyMovementDecorator>(unit));

    else if (std::dynamic_pointer_cast<HeroUnit>(unit) != nullptr)
        killed(std::dynamic_pointer_cast<HeroUnit>(unit));
}

void LoggingModule::killed(std::shared_ptr<HeroUnit> hero_unit){
    addMessage("HeroUnit was killed at position: " + convertVectorToString(hero_unit->position));
    printMessages();
}

void LoggingModule::killed(std::shared_ptr<WeakEnemyUnit> enemy_unit){
    addMessage("WeakEnemyUnit was killed at position: " + convertVectorToString(enemy_unit->position));
    printMessages();
}

void LoggingModule::killed(std::shared_ptr<StrongEnemyUnit> enemy_unit){
    addMessage("StrongEnemyUnit was killed at position: " + convertVectorToString(enemy_unit->position));
    printMessages();
}

void LoggingModule::killed(std::shared_ptr<MightyEnemyUnit> enemy_unit){
    addMessage("MightyEnemyUnit was killed at position: " + convertVectorToString(enemy_unit->position));
    printMessages();
}

void LoggingModule::killed(std::shared_ptr<EnemySuperAttackDecorator> decorator){
    addMessage("Decorated EnemyUnit with super attack was killed at position: " + convertVectorToString(decorator->position));
    printMessages();
}

void LoggingModule::killed(std::shared_ptr<EnemyMovementDecorator> decorator){
    addMessage("Decorated EnemyUnit with movement was killed at position: " + convertVectorToString(decorator->position));
    printMessages();
}
