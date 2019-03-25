#pragma once

class Vector{
public:
	double x, y;
	Vector();
	Vector(double x, double y);
	Vector& operator+=(const Vector& nxt);
};