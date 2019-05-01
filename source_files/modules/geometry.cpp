#include <cmath>

#include <geometry.h>

#include <math_settings.h>

Vector::Vector(){}

Vector::Vector(double x, double y): x(x), y(y){}

Vector Vector::operator*(double value){
    return Vector(x * value, y * value);
}

Vector Vector::operator/(double value){
    return Vector(x / value, y / value);
}

Vector Vector::operator-(const Vector& next){
    return Vector(x - next.x, y - next.y);
}

Vector Vector::operator+(const Vector& next){
    return Vector(x + next.x, y + next.y);
}

Vector& Vector::operator+=(const Vector& next){
    x += next.x;
    y += next.y;
    return *this;
}

Vector& Vector::operator-=(const Vector& next){
    x -= next.x;
    y -= next.y;
    return *this;
}

double Vector::length(){
    return sqrt(x * x + y * y);
}

double Vector::getAngleInDegrees(){
    double value = atan2(y, x);
    if (value < 0) value += 2 * PI;
    return 180 * value / PI;
}

Vector Vector::resize(double new_length){
    if (length() < eps9){
        return *this;
    }
    new_length /= length();
    return Vector(x * new_length, y * new_length);
}

Vector Vector::rotate(double angle){
    return Vector(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
}
