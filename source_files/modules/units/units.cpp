#pragma once
#include "units.h"

void WeakEnemyUnit::update(double time){}
void StrongEnemyUnit::update(double time){}
void MightyEnemyUnit::update(double time){}

/* =============================================================== HERO UNIT =============================================================== */

void HeroUnit::moveUp(double value){
	position.y -= value;
}

void HeroUnit::moveDown(double value){
	position.y += value;
}

void HeroUnit::moveLeft(double value){
	position.x -= value;
}

void HeroUnit::moveRight(double value){
	position.x += value;
}

void HeroUnit::checkBorder(){
	auto shape_bounds = shape->getLocalBounds();
	position.x = std::max(position.x, (double)shape_bounds.width / 2);
	position.y = std::max(position.y, (double)shape_bounds.height / 2);
	position.x = std::min(position.x, WINDOW_HEIGHT - (double)shape_bounds.width / 2);
	position.y = std::min(position.y, WINDOW_WIDTH - (double)shape_bounds.height / 2);
}

void HeroUnit::update(double time){
	int dx = 0, dy = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dy -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dx -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dy += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dx += 1;

	double value = time * HERO_MOVE_SPEED;
	if (dx != 0 && dy != 0) value /= sqrt(2);

	if (dx == -1) moveLeft(value);
	if (dx == 1) moveRight(value);
	if (dy == -1) moveUp(value);
	if (dy == 1) moveDown(value);

	checkBorder();
}