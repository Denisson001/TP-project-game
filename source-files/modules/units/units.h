#include <SFML/Graphics.hpp>
#include "../geometry/geometry.cpp"

class Unit{
public:
	Vector position;	
	sf::Shape* shape;
	virtual ~Unit(){}
};

class WeakEnemyUnit : public Unit{

};

class StrongEnemyUnit : public Unit{

};

class MightyEnemyUnit : public Unit{

};

/*
class Hero : public Unit{

};
*/