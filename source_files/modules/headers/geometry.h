#pragma once

class Vector{
public:
	double x, y;
	Vector();
	Vector(double x, double y);
	Vector operator*(double value);
	Vector operator-(const Vector& next);
	Vector operator+(const Vector& next);
	Vector& operator-=(const Vector& next);
	Vector& operator+=(const Vector& next);
	double length();
	double getAngleInDegrees();
	Vector resize(double new_length);
	Vector rotate(double angle);
};
