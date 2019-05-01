#include <boost/test/unit_test.hpp>

#include <memory>

#include <testing_module.h>
#include <units_factories.h>
#include <game_proxy.h>
#include <fake_controller.h>
#include <logging_module.h>
#include <text_helper.h>

#include <fstream>

#include <technical_settings.h>

BOOST_AUTO_TEST_SUITE(LOGGING_MODULE)

std::shared_ptr<Game> initializeGame(){
    GameProxy::initialize(CircleUnitsFactory::getInstance(), SquareUnitsFactory::getInstance(), std::make_shared<FakeController>("00000000"));
    return TestingModule::getGameInstance();
}

void readWords(std::fstream& file, int words_amount){
	for (int i = 0; i < words_amount; i++){
		std::string str;
		file >> str;
	}
}

BOOST_AUTO_TEST_CASE(initialize_method){
	int seed = 12321;
	LoggingModule::initialize(seed);
    std::fstream file(LOG_FILE_PATH, std::fstream::in);
    readWords(file, 5);
    std::string str_seed;
    file >> str_seed;
    BOOST_CHECK(str_seed == "12321");
    file.close();
}

void checkWord(std::string word, int word_number){
	std::fstream file(LOG_FILE_PATH, std::fstream::in);
    readWords(file, word_number - 1);
    std::string current_str_unit;
    file >> current_str_unit;
    BOOST_CHECK(current_str_unit == word);
    file.close();
}

void checkCreatedMethod(std::shared_ptr<Unit> unit, std::string str_unit){
	LoggingModule::initialize(0);
	LoggingModule::created(unit);
	checkWord(str_unit, 8);
}

void checkKilledMethod(std::shared_ptr<Unit> unit, std::string str_unit){
	LoggingModule::initialize(0);
	LoggingModule::killed(unit);
	if (str_unit != "super" && str_unit != "movement"){
		checkWord(str_unit, 8);
	} else {
		checkWord(str_unit, 12);		
	}
}

BOOST_AUTO_TEST_CASE(created_method){
	std::shared_ptr<Game> game = initializeGame();
	UnitsFactory& units_factory = CircleUnitsFactory::getInstance();
	checkCreatedMethod(TestingModule::getHeroUnit(game), "HeroUnit");
	checkCreatedMethod(units_factory.createWeakEnemyUnit(Vector(0, 0)), "WeakEnemyUnit");
	checkCreatedMethod(units_factory.createStrongEnemyUnit(Vector(0, 0)), "StrongEnemyUnit");
	checkCreatedMethod(units_factory.createMightyEnemyUnit(Vector(0, 0)), "MightyEnemyUnit");
	std::shared_ptr<EnemyUnit> enemy_unit = units_factory.createWeakEnemyUnit(Vector(0, 0));
	checkCreatedMethod(std::make_shared<EnemySuperAttackDecorator>(enemy_unit), "EnemySuperAttackDecorator");
	checkCreatedMethod(std::make_shared<EnemyMovementDecorator>(enemy_unit), "EnemyMovementDecorator");
}

BOOST_AUTO_TEST_CASE(killed_method){
	std::shared_ptr<Game> game = initializeGame();
	UnitsFactory& units_factory = CircleUnitsFactory::getInstance();
	checkKilledMethod(TestingModule::getHeroUnit(game), "HeroUnit");
	checkKilledMethod(units_factory.createWeakEnemyUnit(Vector(0, 0)), "WeakEnemyUnit");
	checkKilledMethod(units_factory.createStrongEnemyUnit(Vector(0, 0)), "StrongEnemyUnit");
	checkKilledMethod(units_factory.createMightyEnemyUnit(Vector(0, 0)), "MightyEnemyUnit");
	std::shared_ptr<EnemyUnit> enemy_unit = units_factory.createWeakEnemyUnit(Vector(0, 0));
	checkKilledMethod(std::make_shared<EnemySuperAttackDecorator>(enemy_unit), "super");
	checkKilledMethod(std::make_shared<EnemyMovementDecorator>(enemy_unit), "movement");
}

BOOST_AUTO_TEST_CASE(addMessage_printMessages_methods){
	initializeGame();
	LoggingModule::initialize(0);
	std::string words[3] = {"123", "abcde", "*/[]{}()@#$^&!?"};
	for (int i = 0; i < 3; i++){
		TestingModule::addMessage(words[i]);
	}
	TestingModule::printMessages();
	for (int i = 0; i < 3; i++){
		checkWord(words[i], i + 8);
	}
}

BOOST_AUTO_TEST_CASE(addHeroUnitSettings_methods){
	std::shared_ptr<Game> game = initializeGame();
	LoggingModule::initialize(0);
	std::shared_ptr<HeroUnit> hero_unit = TestingModule::getHeroUnit(game);
	TestingModule::addHeroUnitSettings(hero_unit);
	TestingModule::printMessages();
	checkWord(TextHelper::convertIntToString(hero_unit->getDamage()), 9);
	checkWord(TextHelper::convertIntToString(hero_unit->getHealth()), 11);
	checkWord(TextHelper::convertIntToString((int)hero_unit->getAttackRange()), 14);
	checkWord(TextHelper::convertIntToString((int)hero_unit->getMaxAttackCooldown()), 17);
}

BOOST_AUTO_TEST_CASE(addEnemyUnitSettings_methods){
	initializeGame();
	LoggingModule::initialize(0);
	std::shared_ptr<EnemyUnit> enemy_unit = SquareUnitsFactory::getInstance().createStrongEnemyUnit(Vector(0, 0));
	TestingModule::addEnemyUnitSettings(enemy_unit);
	TestingModule::printMessages();
	checkWord(TextHelper::convertIntToString(enemy_unit->getDamage()), 9);
	checkWord(TextHelper::convertIntToString(enemy_unit->getHealth()), 11);
	checkWord(TextHelper::convertIntToString((int)enemy_unit->getAttackRange()), 14);
	checkWord(TextHelper::convertIntToString((int)enemy_unit->getMaxAttackCooldown()), 17);
}

BOOST_AUTO_TEST_SUITE_END()