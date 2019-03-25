#include <geometry.h>

Vector::Vector(){}

Vector::Vector(double x, double y): x(x), y(y){}

Vector& Vector::operator+=(const Vector& nxt){
	this->x += nxt.x;
	this->y += nxt.y;
	return *this;
}