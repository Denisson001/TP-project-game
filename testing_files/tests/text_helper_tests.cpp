#include <boost/test/unit_test.hpp>

#include <geometry.h>
#include <text_helper.h>

BOOST_AUTO_TEST_SUITE(TEXT_HELPER)

BOOST_AUTO_TEST_CASE(convertIntToString_method){
	BOOST_CHECK(TextHelper::convertIntToString(0) == "0");
	BOOST_CHECK(TextHelper::convertIntToString(42) == "42");
	BOOST_CHECK(TextHelper::convertIntToString(-1) == "-1");
	BOOST_CHECK(TextHelper::convertIntToString((int)1e9) == "1000000000");
}

BOOST_AUTO_TEST_CASE(convertVectorToString_method){
	BOOST_CHECK(TextHelper::convertVectorToString(Vector(0, 0)) == "(0, 0)");
	BOOST_CHECK(TextHelper::convertVectorToString(Vector(12, 13)) == "(12, 13)");
	BOOST_CHECK(TextHelper::convertVectorToString(Vector(42.4, 42.5)) == "(42, 42)");
	BOOST_CHECK(TextHelper::convertVectorToString(Vector(-1, -2.3)) == "(-1, -2)");
}

BOOST_AUTO_TEST_CASE(convertTimeToString_method){
	BOOST_CHECK(TextHelper::convertTimeToString(0) == "[00:00]");
	BOOST_CHECK(TextHelper::convertTimeToString(60) == "[01:00]");
	BOOST_CHECK(TextHelper::convertTimeToString(123 * 60 + 45) == "[123:45]");
	BOOST_CHECK(TextHelper::convertTimeToString(128.9) == "[02:08]");
}

BOOST_AUTO_TEST_CASE(applyTimeFormat_method){
	BOOST_CHECK(TextHelper::applyTimeFormat(0) == "00");
	BOOST_CHECK(TextHelper::applyTimeFormat(9) == "09");
	BOOST_CHECK(TextHelper::applyTimeFormat(10) == "10");
	BOOST_CHECK(TextHelper::applyTimeFormat(111) == "111");
}

BOOST_AUTO_TEST_SUITE_END()