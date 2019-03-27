#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include <game.h>
#include <units_factories.h>

class TestingModule{
public:
	static std::shared_ptr<sf::Shape> callCreateUnitShapeFromCircleUnitsFactory(double unit_shape_size, sf::Color unit_shape_color);
	static std::shared_ptr<sf::Shape> callCreateUnitShapeFromSquareUnitsFactory(double unit_shape_size, sf::Color unit_shape_color);
	static void callUpdateMovementModuleFromHeroUnit(std::shared_ptr<HeroUnit> unit, double time);
	static UnitsFactory& getEnemyUnitsFactoryFromGame(Game& game);
	static std::shared_ptr<HeroUnit> getHeroUnitFromGame(Game& game);
};