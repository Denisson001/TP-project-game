#include <boost/test/unit_test.hpp>

#include <geometry.h>

#include <math_settings.h>
#include <math_settings.h>

BOOST_AUTO_TEST_SUITE(GEOMETRY)

BOOST_AUTO_TEST_CASE(vector_contructor){
    Vector vector(4.2, -4.2);
    BOOST_CHECK_CLOSE_FRACTION(vector.x, 4.2, eps9);
    BOOST_CHECK_CLOSE_FRACTION(vector.y, -4.2, eps9);
}

BOOST_AUTO_TEST_CASE(multiplication_on_double_operator){
    Vector vector(1, -1);
    vector = vector * 3.1;
    BOOST_CHECK_CLOSE_FRACTION(vector.x, 3.1, eps9);
    BOOST_CHECK_CLOSE_FRACTION(vector.y, -3.1, eps9);
}

BOOST_AUTO_TEST_CASE(subtraction_operator){
    Vector vector(1, -2);
    vector = vector - Vector(2.5, -2);
    BOOST_CHECK_CLOSE_FRACTION(vector.x, -1.5, eps9);
    BOOST_CHECK_CLOSE_FRACTION(vector.y, 0, eps9);
}

BOOST_AUTO_TEST_CASE(addition_operator){
    Vector vector(2, -1);
    vector = vector + Vector(2.5, -2);
    BOOST_CHECK_CLOSE_FRACTION(vector.x, 4.5, eps9);
    BOOST_CHECK_CLOSE_FRACTION(vector.y, -3, eps9);
}

BOOST_AUTO_TEST_CASE(subtraction_assignment_operator){
    Vector vector(1, -2);
    vector -= Vector(2.5, -2);
    BOOST_CHECK_CLOSE_FRACTION(vector.x, -1.5, eps9);
    BOOST_CHECK_CLOSE_FRACTION(vector.y, 0, eps9);
}

BOOST_AUTO_TEST_CASE(addition_assignment_operator){
    Vector vector(2, -1);
    vector += Vector(2.5, -2);
    BOOST_CHECK_CLOSE_FRACTION(vector.x, 4.5, eps9);
    BOOST_CHECK_CLOSE_FRACTION(vector.y, -3, eps9);
}

BOOST_AUTO_TEST_CASE(length_method){
    Vector vector(7, -3);
    BOOST_CHECK_CLOSE_FRACTION(vector.length(), sqrt(7 * 7 + 3 * 3), eps9);
}

BOOST_AUTO_TEST_CASE(getAngleInDegress_method){
    Vector vector(1, 1);
    double value = vector.getAngleInDegrees();
    BOOST_CHECK_CLOSE_FRACTION(value, 45, eps9);
}

BOOST_AUTO_TEST_CASE(resize_method){
    Vector vector(6, 8);
    vector = vector.resize(5);
    BOOST_CHECK_CLOSE_FRACTION(vector.x, 3, eps9);
    BOOST_CHECK_CLOSE_FRACTION(vector.y, 4, eps9);
}

BOOST_AUTO_TEST_CASE(rotate_method){
    Vector vector(-1, 1);
    vector = vector.rotate(PI / 2);
    BOOST_CHECK_CLOSE_FRACTION(vector.x, -1, eps9);
    BOOST_CHECK_CLOSE_FRACTION(vector.y, -1, eps9);
}

BOOST_AUTO_TEST_SUITE_END()
