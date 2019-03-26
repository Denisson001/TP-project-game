#include <boost/test/unit_test.hpp>

#include <geometry.h>

const double eps9 = 1e-9;

BOOST_AUTO_TEST_SUITE(GEOMETRY)

BOOST_AUTO_TEST_CASE(vector){
	Vector v(4.2, -4.2);
	BOOST_CHECK_CLOSE_FRACTION(v.x, 4.2, eps9);
	BOOST_CHECK_CLOSE_FRACTION(v.y, -4.2, eps9);
}

BOOST_AUTO_TEST_SUITE_END()
