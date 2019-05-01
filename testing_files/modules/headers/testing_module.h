#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include <game.h>
#include <game_proxy.h>
#include <enemy_units_booster.h>
#include <hero_unit_attack_module.h>
#include <enemy_units_decorators.h>
#include <logging_module.h>

class TestingModule{
public:
	//GameProxy
	static std::shared_ptr<Game> getGameInstance();
	//Game
	static std::shared_ptr<HeroUnit> getHeroUnit(std::shared_ptr<Game> game);
	static std::vector<std::shared_ptr<EnemyUnit>>& getEnemyUnits(std::shared_ptr<Game> game);
	static std::vector<std::shared_ptr<Bullet>>& getHeroUnitBullets(std::shared_ptr<Game> game);
	static std::vector<std::shared_ptr<Bullet>>& getEnemyUnitsBullets(std::shared_ptr<Game> game);
	static std::pair<int, int> getRandomFreeGridCell(std::shared_ptr<Game> game);
	static void updateEnemyUnitsBullets(std::shared_ptr<Game> game, double time);
	static void updateHeroUnitBullets(std::shared_ptr<Game> game, double time);
	static void eraseFromVector(std::shared_ptr<Game> game, std::vector<std::shared_ptr<EnemyUnit>>& vector, int& index);
	//UnitsFactory
	static std::shared_ptr<sf::Shape> createCircleUnitShape(UnitsFactory& units_factory, double unit_shape_size, sf::Color unit_shape_color);
	//HeroUnit
	static void updateAttackModule(std::shared_ptr<HeroUnit> hero_unit, double time);
	static void updateMovementModule(std::shared_ptr<HeroUnit> hero_unit, double time);
	static void addBullet(std::shared_ptr<HeroUnit> hero_unit, Vector direction);
	static void changeAttackModule(std::shared_ptr<HeroUnit> hero_unit);
	static int getCurrentAttackModuleNumber(std::shared_ptr<HeroUnit> hero_unit);
	//HeroUnitAttackModule
	static std::pair<int, int> getDirectionFromController(std::shared_ptr<HeroUnitAttackModule> attack_module, std::shared_ptr<Controller> controller);
	//EnemyUnit
	static void updateAttackModule(std::shared_ptr<EnemyUnit> enemy_unit, double time);
	static void updateMovementModule(std::shared_ptr<EnemyUnit> enemy_unit, double time);
	//EnemyMovementDecorator
	static void addBullet(std::shared_ptr<EnemyUnit> enemy_unit, Vector direction);
	static Vector convertGridCellToVector(std::shared_ptr<EnemyMovementDecorator> decorated_enemy_unit, std::pair<int, int> cell_index);
	static void setNewGridPosition(std::shared_ptr<EnemyMovementDecorator> decorated_enemy_unit);
	static std::pair<int, int> getNewGridPosition(std::shared_ptr<EnemyMovementDecorator> decorated_enemy_unit);
	//LoggingModule
    static void printMessages();
    static void addMessage(const std::string& str);
    static void addEnemyUnitSettings(std::shared_ptr<EnemyUnit> enemy_unit);
    static void addHeroUnitSettings(std::shared_ptr<HeroUnit> hero_unit);
    //EnemyUnitsBooster
	static int getEnemyUnitsAmount();
};
