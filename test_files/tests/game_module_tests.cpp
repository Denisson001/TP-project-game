#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>

#include <game.h>

#include <testing_module.h>

UnitsFactory& getFactory(int v){
	if (v == 0) 
		return CircleUnitsFactory::getInstance();
	else
		return SquareUnitsFactory::getInstance();
}

BOOST_AUTO_TEST_SUITE(GAME_MODULE)

BOOST_AUTO_TEST_CASE(game_module_constructor){
	for (int mask = 0; mask < (1 << 2); mask++){
		UnitsFactory& enemy_units_factory = getFactory(mask & 1);
		UnitsFactory& hero_unit_factory = getFactory((mask >> 1) & 1);
		Game game(enemy_units_factory, hero_unit_factory);

		if (mask & 1) BOOST_CHECK_NO_THROW(dynamic_cast<SquareUnitsFactory&>(TestingModule::getEnemyUnitsFactoryFromGame(game)));
		if (!(mask & 1)) BOOST_CHECK_NO_THROW(dynamic_cast<CircleUnitsFactory&>(TestingModule::getEnemyUnitsFactoryFromGame(game)));

		if ((mask >> 1) & 1) BOOST_CHECK(dynamic_cast<sf::RectangleShape*>(TestingModule::getHeroUnitFromGame(game)->shape.get()));
		if (!((mask >> 1) & 1)) BOOST_CHECK(dynamic_cast<sf::CircleShape*>(TestingModule::getHeroUnitFromGame(game)->shape.get()));
	}
}

BOOST_AUTO_TEST_SUITE_END()
