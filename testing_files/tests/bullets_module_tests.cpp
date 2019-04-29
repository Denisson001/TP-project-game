#include <boost/test/unit_test.hpp>

#include <bullet.h>

const double eps9 = 1e-9;

BOOST_AUTO_TEST_SUITE(BULLET)

BOOST_AUTO_TEST_CASE(bullet_contructor){
    Vector position(4.2, -4.2);
    Vector direction(1, 1);
    int damage = 10;
    int range = 100;
	Bullet bullet(sf::Color::White, position, direction, damage, range);
    BOOST_CHECK_CLOSE_FRACTION(bullet.position.x, position.x, eps9);
	BOOST_CHECK_CLOSE_FRACTION(bullet.position.y, position.y, eps9);
    BOOST_CHECK_CLOSE_FRACTION(bullet.vector.x, direction.x, eps9);
	BOOST_CHECK_CLOSE_FRACTION(bullet.vector.y, direction.y, eps9);
    BOOST_CHECK_CLOSE_FRACTION(bullet.damage, damage, eps9);
	BOOST_CHECK_CLOSE_FRACTION(bullet.range, range, eps9);
}

BOOST_AUTO_TEST_CASE(update_method){
    Vector position(0, 0);
    Vector direction(1, 1);
    int damage = 0;
    int range = 1000;
	Bullet bullet(sf::Color::White, position, direction, damage, range);
    double time = 50;
    bullet.update(time);
    BOOST_CHECK_CLOSE_FRACTION(bullet.position.x, position.x + direction.x * time, eps9);
	BOOST_CHECK_CLOSE_FRACTION(bullet.position.y, position.y + direction.y * time, eps9);
    BOOST_CHECK_CLOSE_FRACTION(bullet.range, range - (direction * time).length(), eps9);
}

BOOST_AUTO_TEST_SUITE_END()
