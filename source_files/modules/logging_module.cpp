#include <logging_module.h>

#include <game_proxy.h>
#include <text_helper.h>

#include <fstream>

#include <technical_settings.h>

std::vector<std::string> LoggingModule::text;

void LoggingModule::printMessages(){
    if (text.size() == 0){
        return;
    }
    std::ofstream file;
    file.open(LOG_FILE_PATH, std::fstream::app);
    std::string time = TextHelper::convertTimeToString(GameProxy::getTime() / 1000) + " ";
    file << time << text[0] << "\n";
    for (int i = 1; i < (int)text.size(); i++){
        for (int j = 0; j < (int)time.size(); j++){
            file << " ";
        }
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

void LoggingModule::addHeroUnitSettings(std::shared_ptr<HeroUnit> hero_unit){
    addMessage("Damage: " + TextHelper::convertIntToString(hero_unit->getDamage()));
    addMessage("Health: " + TextHelper::convertIntToString(hero_unit->getHealth()));
    addMessage("Attack range: " + TextHelper::convertIntToString(hero_unit->getAttackRange()));
}

void LoggingModule::addEnemyUnitSettings(std::shared_ptr<EnemyUnit> enemy_unit){
    addMessage("Damage: " + TextHelper::convertIntToString(enemy_unit->getDamage()));
    addMessage("Health: " + TextHelper::convertIntToString(enemy_unit->getHealth()));
    addMessage("Attack range: " + TextHelper::convertIntToString(enemy_unit->getAttackRange()));
    addMessage("Attack cooldown: " + TextHelper::convertIntToString(enemy_unit->getMaxAttackCooldown()));
}

void LoggingModule::created(std::shared_ptr<Unit> unit){
    if (std::dynamic_pointer_cast<WeakEnemyUnit>(unit) != nullptr){
        created(std::dynamic_pointer_cast<WeakEnemyUnit>(unit));

    } else if (std::dynamic_pointer_cast<StrongEnemyUnit>(unit) != nullptr){
        created(std::dynamic_pointer_cast<StrongEnemyUnit>(unit));

    } else if (std::dynamic_pointer_cast<MightyEnemyUnit>(unit) != nullptr){
        created(std::dynamic_pointer_cast<MightyEnemyUnit>(unit));

    } else if (std::dynamic_pointer_cast<EnemySuperAttackDecorator>(unit) != nullptr){
        created(std::dynamic_pointer_cast<EnemySuperAttackDecorator>(unit));

    } else if (std::dynamic_pointer_cast<EnemyMovementDecorator>(unit) != nullptr){
        created(std::dynamic_pointer_cast<EnemyMovementDecorator>(unit));

    } else if (std::dynamic_pointer_cast<HeroUnit>(unit) != nullptr){
        created(std::dynamic_pointer_cast<HeroUnit>(unit));
    }
}

void LoggingModule::created(std::shared_ptr<HeroUnit> hero_unit){
    addMessage("HeroUnit created at position: " + TextHelper::convertVectorToString(hero_unit->getPosition()));
    addHeroUnitSettings(hero_unit);
    printMessages();
}

void LoggingModule::created(std::shared_ptr<WeakEnemyUnit> enemy_unit){
    addMessage("WeakEnemyUnit created at position: " + TextHelper::convertVectorToString(enemy_unit->getPosition()));
    addEnemyUnitSettings(enemy_unit);
    printMessages();
}

void LoggingModule::created(std::shared_ptr<StrongEnemyUnit> enemy_unit){
    addMessage("StrongEnemyUnit created at position: " + TextHelper::convertVectorToString(enemy_unit->getPosition()));
    addEnemyUnitSettings(enemy_unit);
    printMessages();
}

void LoggingModule::created(std::shared_ptr<MightyEnemyUnit> enemy_unit){
    addMessage("MightyEnemyUnit created at position: " + TextHelper::convertVectorToString(enemy_unit->getPosition()));
    addEnemyUnitSettings(enemy_unit);
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
    if (std::dynamic_pointer_cast<WeakEnemyUnit>(unit) != nullptr){
        killed(std::dynamic_pointer_cast<WeakEnemyUnit>(unit));

    } else if (std::dynamic_pointer_cast<StrongEnemyUnit>(unit) != nullptr){
        killed(std::dynamic_pointer_cast<StrongEnemyUnit>(unit));

    } else if (std::dynamic_pointer_cast<MightyEnemyUnit>(unit) != nullptr){
        killed(std::dynamic_pointer_cast<MightyEnemyUnit>(unit));

    } else if (std::dynamic_pointer_cast<EnemySuperAttackDecorator>(unit) != nullptr){
        killed(std::dynamic_pointer_cast<EnemySuperAttackDecorator>(unit));

    } else if (std::dynamic_pointer_cast<EnemyMovementDecorator>(unit) != nullptr){
        killed(std::dynamic_pointer_cast<EnemyMovementDecorator>(unit));

    } else if (std::dynamic_pointer_cast<HeroUnit>(unit) != nullptr){
        killed(std::dynamic_pointer_cast<HeroUnit>(unit));
    }
}

void LoggingModule::killed(std::shared_ptr<HeroUnit> hero_unit){
    addMessage("HeroUnit was killed at position: " + TextHelper::convertVectorToString(hero_unit->getPosition()));
    printMessages();
}

void LoggingModule::killed(std::shared_ptr<WeakEnemyUnit> enemy_unit){
    addMessage("WeakEnemyUnit was killed at position: " + TextHelper::convertVectorToString(enemy_unit->getPosition()));
    printMessages();
}

void LoggingModule::killed(std::shared_ptr<StrongEnemyUnit> enemy_unit){
    addMessage("StrongEnemyUnit was killed at position: " + TextHelper::convertVectorToString(enemy_unit->getPosition()));
    printMessages();
}

void LoggingModule::killed(std::shared_ptr<MightyEnemyUnit> enemy_unit){
    addMessage("MightyEnemyUnit was killed at position: " + TextHelper::convertVectorToString(enemy_unit->getPosition()));
    printMessages();
}

void LoggingModule::killed(std::shared_ptr<EnemySuperAttackDecorator> decorator){
    addMessage("Decorated EnemyUnit with super attack was killed at position: " + TextHelper::convertVectorToString(decorator->getPosition()));
    printMessages();
}

void LoggingModule::killed(std::shared_ptr<EnemyMovementDecorator> decorator){
    addMessage("Decorated EnemyUnit with movement was killed at position: " + TextHelper::convertVectorToString(decorator->getPosition()));
    printMessages();
}
