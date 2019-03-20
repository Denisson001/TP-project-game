#pragma once
#include "units.h"

void HeroUnit::update(double time){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		position.y -= HERO_MOVE_SPEED * time;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		position.x -= HERO_MOVE_SPEED * time;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		position.y += HERO_MOVE_SPEED * time;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		position.x += HERO_MOVE_SPEED * time;
	}
}

void WeakEnemyUnit::update(double time){}
void StrongEnemyUnit::update(double time){}
void MightyEnemyUnit::update(double time){}