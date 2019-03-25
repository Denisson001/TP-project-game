#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <algorithm>

#include <geometry.h>
#include <controller.h>
#include <window_settings.h>
#include <units_settings.h>

class HeroUnit{
private:
	void checkBorder();
	void updateMovementModule(double time);
public:
	std::shared_ptr<Controller> controller;
	Vector position;	
	std::shared_ptr<sf::Shape> shape;
	void update(double time);
};
